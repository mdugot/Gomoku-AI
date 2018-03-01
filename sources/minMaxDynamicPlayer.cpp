#include "minMaxDynamicPlayer.h"
#include "rules.h"

const unsigned char MinMaxDynamicPlayer::depthWidths[10] = {20, 20, 10, 10, 10, 10, 10, 6, 6, 6};

Choice::Choice(unsigned char x, unsigned char y, HeuristicBoard *myHeuristic, HeuristicBoard *ennemyHeuristic, bool ennemy) : x(x), y(y), myHeuristic(myHeuristic), ennemyHeuristic(ennemyHeuristic)
{
	if (!ennemy) {
		this->myHeuristic.put(x, y);
		this->ennemyHeuristic.clear(x, y);
	} else {
		this->myHeuristic.clear(x, y);
		this->ennemyHeuristic.put(x, y);
	}
}

Choice::Choice() : x(0), y(0), myHeuristic(), ennemyHeuristic()
{
}

Choice::~Choice()
{
}


MinMaxDynamicPlayer::MinMaxDynamicPlayer(int d) : Player(), minMaxDepth(d), myHeuristic(), ennemyHeuristic()
{
	if (d > 10)
		failure("max depth = 10");
}

MinMaxDynamicPlayer::~MinMaxDynamicPlayer()
{
}

std::map<long long, Choice> MinMaxDynamicPlayer::heuristicMap(Rules &rules, Player *player, int depth, HeuristicBoard &myOrigin, HeuristicBoard &ennemyOrigin, bool focus) {
	std::map<long long, Choice> result;
	for (unsigned char j = 0; j < GH; j++) {
		for (unsigned char i = 0; i < GW; i++) {
			if ((!focus || gomoku->isFocus(i, j)) && rules.canPutStone(*player, i, j)) {

				if (player == this) {
					Choice choice(i, j, &myOrigin, &ennemyOrigin);
					result[-heuristic(choice.myHeuristic, choice.ennemyHeuristic, depth)] = choice;
//					if (focus)
//						DEBUG << DARK_YELLOW << "option : " << -heuristic(choice.myHeuristic, choice.ennemyHeuristic, depth) << "=" << (int)choice.x << "/" << (int)choice.y << "\n" << DEFAULT_COLOR;
				} else {
					Choice choice(i, j, &myOrigin, &ennemyOrigin, true);
					result[heuristic(choice.myHeuristic, choice.ennemyHeuristic, depth, true)] = choice;
				}
			}
		}
	}
	return result;
}

bool MinMaxDynamicPlayer::win(int &rx, int &ry, Rules &rules) {
	for (unsigned char j = 0; j < GH; j++) {
		for (unsigned char i = 0; i < GW; i++) {
			if (rules.canPutStone(*this, i, j)) {
				if (myHeuristic.getBestLevel(i, j) >= 4) {
					rx = i;
					ry = j;
					return true;
				}
			}
		}
	}
	return false;
}

void MinMaxDynamicPlayer::startMinMax(int &rx, int &ry, Rules &rules)
{
	long long option;
	long long best = MIN_LONG;
	long long maxBestOption = MIN_LONG;
	complexity = 0;
	std::map<long long, Choice> choices = heuristicMap(rules, this, minMaxDepth, myHeuristic, ennemyHeuristic, true);
	rx = choices.begin()->second.x;
	ry = choices.begin()->second.y;
	unsigned char i = 0;
	if (ennemyHeuristic.score >= L4) {
//		DEBUG << RED << "DANGER ZONE\n" << DEFAULT_COLOR;
		i = depthWidths[0];
	}
	for (auto it = choices.begin(); it != choices.end(); ++it) {
		if (i > depthWidths[0]) {
//			DEBUG << "WIDTH BREAK\n";
			break;
		}
//		DEBUG << YELLOW << "choice : " << it->first << "=" << (int)it->second.x << "/" << (int)it->second.y << "\n" << DEFAULT_COLOR;
		gomoku->setStone(getColor(), it->second.x, it->second.y);
//		gomoku->printBoard(it->second.x, it->second.y);
//		it->second.myHeuristic.print();
//		DEBUG << "my score = " << it->second.myHeuristic.score << "\n";
//		it->second.ennemyHeuristic.print(it->second.x, it->second.y);
//		DEBUG << "ennemy score = " << it->second.ennemyHeuristic.score << "\n";
		complexity++;
		option = min(minMaxDepth, MAX_LONG, maxBestOption, rules, it->second.myHeuristic, it->second.ennemyHeuristic);
//		DEBUG << DARK_YELLOW << "prediction : " << option << "\n" << DEFAULT_COLOR;
		gomoku->setStone(FREE, it->second.x, it->second.y);
		if (option > best) {
			best = option;
			rx = it->second.x;
			ry = it->second.y;
//			if (best >= WIN_STATE) {
//				DEBUG << "WIN BREAK\n";
//				break;
//			}
		}
		if (option > maxBestOption) {
			maxBestOption = option;
		}
		i++;
	}
	DEBUG << "complexity : " << complexity << "\n";
}

long long MinMaxDynamicPlayer::max(int depth, long long minBestOption, long long maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH)
{
	if (depth <= 0 || myH.score >= HAS_WON || ennemyH.score >= HAS_WON) {
//		if (depth == 8) DEBUG << ">end : " << heuristic(myH, ennemyH, depth+1, true) << "\n";
		return heuristic(myH, ennemyH, depth+1, true);
	}
	long long option;
	long long best = MIN_LONG;
	std::map<long long, Choice> choices = heuristicMap(rules, this, depth, myH, ennemyH);
	unsigned char i = 0;
//	if (ennemyH.score >= L4) {
//		if (depth == 8) DEBUG << RED << ">DANGER ZONE (" << ennemyH.score << ")\n" << DEFAULT_COLOR;
//		i = depthWidths[minMaxDepth - depth];
//	}
	for (auto it = choices.begin(); it != choices.end(); ++it) {
		if (i > depthWidths[minMaxDepth - depth]) {
//			DEBUG << CYAN << "width break\n" << DEFAULT_COLOR;
			break;
		}
//		DEBUG << CYAN << "choice : " << it->first << "=" << (int)it->second.x << "/" << (int)it->second.y << "\n" << DEFAULT_COLOR;
		gomoku->setStone(getColor(), it->second.x, it->second.y);
		complexity++;
		option = min(depth-1, minBestOption, maxBestOption, rules, it->second.myHeuristic, it->second.ennemyHeuristic);
//		DEBUG << DARK_CYAN << "prediction : " << option << "\n" << DEFAULT_COLOR;
		gomoku->setStone(FREE, it->second.x, it->second.y);
		if (option > best) {
			best = option;
			if (option > maxBestOption) {
				maxBestOption = option;
			}
			if (maxBestOption >= minBestOption - 1) {
//				if (depth == 8) DEBUG << ">alphabeta : " << best << "\n";
//				DEBUG << CYAN << "alpha beta break\n" << DEFAULT_COLOR;
				return best;
			}
		}
		i++;
	}
//	if (depth == 8) DEBUG << ">normal : " << best << "\n";
	return best;
}

long long MinMaxDynamicPlayer::min(int depth, long long minBestOption, long long maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH)
{
	if (depth <= 0 || myH.score >= HAS_WON || ennemyH.score >= HAS_WON) {
		return heuristic(myH, ennemyH, depth+1);
	}
	long long option;
	long long best = MAX_LONG;
//	if (depth == 9) DEBUG << "default : " << best << "\n";
	std::map<long long, Choice> choices = heuristicMap(rules, enemy, depth, myH, ennemyH);
	unsigned char i = 0;
//	if (myH.score >= L4) {
//		i = depthWidths[minMaxDepth - depth];
//	}
	for (auto it = choices.begin(); it != choices.end(); ++it) {
		if (i > depthWidths[minMaxDepth - depth]) {
//			DEBUG << GREEN << "width break\n" << DEFAULT_COLOR;
			break;
		}
//		DEBUG << GREEN << "min choice : " << it->first << "=" << (int)it->second.x << "/" << (int)it->second.y << "\n" << DEFAULT_COLOR;
		gomoku->setStone(enemy->getColor(), it->second.x, it->second.y);
		complexity++;
		option = max(depth-1, minBestOption, maxBestOption, rules, it->second.myHeuristic, it->second.ennemyHeuristic);
//		DEBUG << DARK_GREEN << "min prediction : " << option << "\n" << DEFAULT_COLOR;
		gomoku->setStone(FREE, it->second.x, it->second.y);
		if (option < best) {
			best = option;
//			if (depth == 9) DEBUG << "new : " << best << "\n";
			if (option < minBestOption) {
				minBestOption = option;
			}
			if (maxBestOption >= minBestOption - 1) {
//				if (depth == 9) DEBUG << "result : " << best << "\n";
//				DEBUG << GREEN << "alpha beta break\n" << DEFAULT_COLOR;
				return best;
			}
		}
		i++;
	}
	return best;
}


void MinMaxDynamicPlayer::play(Rules &rules, Interface &i) {
	(void)i;
	int x = -1;
	int y = -1;
	if (!win(x, y, rules)) {
		DEBUG << "BEFORE PLAY\n";
		startMinMax(x, y, rules);
		DEBUG << "AFTER PLAY\n";
	}
	DEBUG << "PUT : " << x << "/" << y << "\n";
	putStone(x, y);
	DEBUG << "SET\n";
	setCoordPlayed(x, y);



	DEBUG << "THREAT HEURISTIC BEFORE STONE = " << heuristic(myHeuristic, ennemyHeuristic, minMaxDepth) << "\n";
	DEBUG << "my score before stone = " << myHeuristic.score << "\n";
	DEBUG << "ennemy score before stone = " << ennemyHeuristic.score << "\n";
	myHeuristic.put(x, y, false);
	ennemyHeuristic.clear(x, y);
	DEBUG << "THREAT HEURISTIC AFTER STONE = " << heuristic(myHeuristic, ennemyHeuristic, minMaxDepth) << "\n";
	DEBUG << "my score after stone = " << myHeuristic.score << "\n";
	DEBUG << "ennemy score after stone = " << ennemyHeuristic.score << "\n";
	myHeuristic.print(x, y);
}

void MinMaxDynamicPlayer::observe(Rules &rules, int x, int y) {
	(void)rules;
	myHeuristic.clear(x, y);
	ennemyHeuristic.put(x, y);
}

long long MinMaxDynamicPlayer::heuristic(HeuristicBoard &myH, HeuristicBoard &ennemyH, int depth, bool ennemy) {
	if (depth <= 0) {
		DEBUG << RED << "NEGATIVE DEPTH !!!!\n" << DEFAULT_COLOR;
	}
	if (myH.score >= HAS_WON) {
//		if (last) DEBUG << PURPLE  << "#I have won" << DEFAULT_COLOR << "\n";
		return BIG * (depth) * 11;
	}
	if (ennemyH.score >= HAS_WON) {
//		if (last) DEBUG << PURPLE  << "#ennemy has won" << DEFAULT_COLOR << "\n";
		return -BIG * (depth) * 11;
	}

	if (ennemy) {
		if (myH.score >= L4) {
			return BIG * (depth);
		}
		if (ennemyH.score >= WIN_STATE) {
//			if (depth == 9) DEBUG << PURPLE  << "#ennemy going to win (depth=" << depth << ", result=" << (-BIG * (depth)) << ", big=" << BIG << ")" << DEFAULT_COLOR << "\n";
			return (-BIG * (depth) - 1);
		}
		return (myH.score * L2) - (ennemyH.score);
	}

	if (ennemyH.score >= L4) {
//		if (depth == 9) DEBUG << PURPLE  << "#I am going to loose" << DEFAULT_COLOR << "\n";
		return -BIG * (depth);
	}
	if (myH.score >= WIN_STATE) {
//		if (last) DEBUG << PURPLE  << "#I am going to win" << DEFAULT_COLOR << "\n";
		return BIG * (depth);
	}
//	if (last) DEBUG << PURPLE  << "#I don't know (ennemy score = " << ennemyH.score << ")" << DEFAULT_COLOR << "\n";
	return myH.score - (ennemyH.score * L2);
}

