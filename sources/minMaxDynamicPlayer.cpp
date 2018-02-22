#include "minMaxDynamicPlayer.h"
#include "rules.h"

const unsigned char MinMaxDynamicPlayer::depthWidths[10] = {10, 7, 6, 5, 4, 3, 3, 3, 3, 3};

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

std::map<int, Choice> MinMaxDynamicPlayer::heuristicMap(Rules &rules, Player *player, bool focus) {
	std::map<int, Choice> result;
	for (unsigned char j = 0; j < GH; j++) {
		for (unsigned char i = 0; i < GW; i++) {
			if ((!focus || gomoku->isFocus(i, j)) && rules.canPutStone(*player, i, j)) {
				if (player == this) {
					Choice choice(i, j, &myHeuristic, &ennemyHeuristic);
					result[-heuristic(choice.myHeuristic, choice.ennemyHeuristic)] = choice;
				} else {
					Choice choice(i, j, &myHeuristic, &ennemyHeuristic, true);
					result[heuristic(choice.myHeuristic, choice.ennemyHeuristic)] = choice;
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
	int option;
	int best = MIN_INT;
	int maxBestOption = MIN_INT;
	complexity = 0;
	std::map<int, Choice> choices = heuristicMap(rules, this, true);
	rx = choices.begin()->second.x;
	ry = choices.begin()->second.y;
	unsigned char i = 0;
	for (auto it = choices.begin(); it != choices.end(); ++it) {
		if (i >= depthWidths[0])
			break;
		gomoku->setStone(getColor(), it->second.x, it->second.y);
		complexity++;
		option = min(minMaxDepth, MAX_INT, maxBestOption, rules, it->second.myHeuristic, it->second.ennemyHeuristic);
		gomoku->setStone(FREE, it->second.x, it->second.y);
		if (option > best) {
			best = option;
			rx = it->second.x;
			ry = it->second.y;
			if (best >= WIN_STATE)
				break;
		}
		if (option > maxBestOption) {
			maxBestOption = option;
		}
		i++;
	}
	DEBUG << "complexity : " << complexity << "\n";
}

int MinMaxDynamicPlayer::max(int depth, int minBestOption, int maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH)
{
//	DEBUG << "MAX\n";
	if (depth <= 0) {
		return heuristic(myH, ennemyH);
	}
	if (myH.score >= L4) {
		return MAX_INT;
	}
	if (ennemyH.score >= WIN_STATE) {
		return MIN_INT;
	}
	int option;
	int best = MIN_INT;
	std::map<int, Choice> choices = heuristicMap(rules, this);
	unsigned char i = 0;
	for (auto it = choices.begin(); it != choices.end(); ++it) {
		if (i >= depthWidths[minMaxDepth - depth])
			break;
		gomoku->setStone(getColor(), it->second.x, it->second.y);
		complexity++;
//		DEBUG << "AAA\n";
		option = min(depth-1, minBestOption, maxBestOption, rules, it->second.myHeuristic, it->second.ennemyHeuristic);
//		DEBUG << "BBB\n";
		gomoku->setStone(FREE, it->second.x, it->second.y);
		if (option > best) {
			best = option;
			if (option > maxBestOption) {
				maxBestOption = option;
			}
			if (maxBestOption >= minBestOption - 1)
				return best;
		}
		i++;
	}
	return best;
}

int MinMaxDynamicPlayer::min(int depth, int minBestOption, int maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH)
{
//	DEBUG << "MIN\n";
	if (depth <= 0) {
		return heuristic(myH, ennemyH);
	}
	if (ennemyH.score >= L4) {
		return MIN_INT;
	}
	if (myH.score >= WIN_STATE) {
		return MAX_INT;
	}
	int option;
	int best = MAX_INT;
	std::map<int, Choice> choices = heuristicMap(rules, ennemy, true);
	unsigned char i = 0;
	for (auto it = choices.begin(); it != choices.end(); ++it) {
		if (i >= depthWidths[minMaxDepth - depth])
			break;
		gomoku->setStone(ennemy->getColor(), it->second.x, it->second.y);
		complexity++;
		option = max(depth-1, minBestOption, maxBestOption, rules, it->second.myHeuristic, it->second.ennemyHeuristic);
		gomoku->setStone(FREE, it->second.x, it->second.y);
		if (option < best) {
			best = option;
			if (option < minBestOption) {
				minBestOption = option;
			}
			if (maxBestOption >= minBestOption - 1) {
				return best;
			}
		}
		i++;
	}
	return best;
}

/*void MinMaxDynamicPlayer::startMinMax(int &rx, int &ry, Rules &rules)
{
	int option;
	int best = MIN_INT;
	int maxBestOption = MIN_INT;
	complexity = 0;
	for (unsigned char i = 0; i < GW; i++) {
		for (unsigned char j = 0; j < GH; j++) {
			if (gomoku->isFocus(i, j) && rules.canPutStone(*this, i, j)) {
				if (rx < 0) {
					rx = i;
					ry = j;
				}
				gomoku->setStone(getColor(), i, j);
				complexity++;
				option = min(minMaxDepth, MAX_INT, maxBestOption, rules, HeuristicBoard(&myHeuristic).put(i, j), HeuristicBoard(&ennemyHeuristic).clear(i, j));
				gomoku->setStone(FREE, i, j);
				if (option > best) {
					best = option;
					rx = i;
					ry = j;
					if (best >= WIN_STATE) {
						i = GW;
						j = GH;
					}
				}
				if (option > maxBestOption) {
					maxBestOption = option;
				}
			}
		}
	}
	DEBUG << "complexity : " << complexity << "\n";
}

int MinMaxDynamicPlayer::max(int depth, int minBestOption, int maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH)
{
//	DEBUG << "MAX\n";
	if (depth <= 0) {
		return heuristic(myH, ennemyH);
	}
	if (myH.score >= WIN_STATE) {
		return MAX_INT;
	}
	int option;
	int best = MIN_INT;
	for (unsigned char i = 0; i < GW; i++) {
		for (unsigned char j = 0; j < GH; j++) {
			if (rules.canPutStone(*this, i, j)) {
				gomoku->setStone(getColor(), i, j);
				complexity++;
//				DEBUG << "AAA\n";
				option = min(depth-1, minBestOption, maxBestOption, rules, HeuristicBoard(&myH).put(i, j), HeuristicBoard(&ennemyH).clear(i, j));
//				DEBUG << "BBB\n";
				gomoku->setStone(FREE, i, j);
				if (option > best) {
					best = option;
					if (option > maxBestOption) {
						maxBestOption = option;
					}
					if (maxBestOption >= minBestOption - 1)
						return best;
				}
			}
		}
	}
	return best;
}

int MinMaxDynamicPlayer::min(int depth, int minBestOption, int maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH)
{
//	DEBUG << "MIN\n";
	if (depth <= 0) {
		return heuristic(myH, ennemyH);
	}
	if (ennemyH.score >= WIN_STATE) {
		return MIN_INT;
	}
	int option;
	int best = MAX_INT;
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			if (rules.canPutStone(*ennemy, i, j)) {
				gomoku->setStone(ennemy->getColor(), i, j);
				complexity++;
				option = max(depth-1, minBestOption, maxBestOption, rules, HeuristicBoard(&myH).clear(i, j), HeuristicBoard(&ennemyH).put(i, j));
				gomoku->setStone(FREE, i, j);
				if (option < best) {
					best = option;
					if (option < minBestOption) {
						minBestOption = option;
					}
					if (maxBestOption >= minBestOption - 1) {
						return best;
					}
				}
			}
		}
	}
	return best;
}*/

void MinMaxDynamicPlayer::play(Rules &rules, int &x, int &y) {
	x = -1;
	y = -1;
	if (!win(x, y, rules)) {
		startMinMax(x, y, rules);
	}
	putStone(x, y);

	DEBUG << "THREAT HEURISTIC BEFORE STONE = " << heuristic(myHeuristic, ennemyHeuristic) << "\n";
	DEBUG << "my score before stone = " << myHeuristic.score << "\n";
	DEBUG << "ennemy score before stone = " << ennemyHeuristic.score << "\n";
	myHeuristic.put(x, y, false);
	ennemyHeuristic.clear(x, y);
	DEBUG << "THREAT HEURISTIC AFTER STONE = " << heuristic(myHeuristic, ennemyHeuristic) << "\n";
	DEBUG << "my score after stone = " << myHeuristic.score << "\n";
	DEBUG << "ennemy score after stone = " << ennemyHeuristic.score << "\n";
	myHeuristic.print();
}

void MinMaxDynamicPlayer::observe(Rules &rules, int x, int y) {
	(void)rules;
	myHeuristic.clear(x, y);
	ennemyHeuristic.put(x, y);
}

int MinMaxDynamicPlayer::heuristic(HeuristicBoard &myH, HeuristicBoard &ennemyH) {
	return myH.score - ennemyH.score;
}

