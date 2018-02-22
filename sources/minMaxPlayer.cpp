#include "minMaxPlayer.h"
#include "rules.h"

MinMaxPlayer::MinMaxPlayer(int d) : Player(), minMaxDepth(d)
{
}

MinMaxPlayer::~MinMaxPlayer()
{
}

AI1::AI1(int d) : MinMaxPlayer(d)
{
}

AI1::~AI1()
{
}

void MinMaxPlayer::startMinMax(int &rx, int &ry, Rules &rules)
{
	int option;
	int best = MIN_INT;
	int maxBestOption = MIN_INT;
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			if (gomoku->isFocus(i, j) && rules.canPutStone(*this, i, j)) {
				//DEBUG << "start : " << i << "/" << j << "\n";
				if (rx < 0) {
					rx = i;
					ry = j;
				}
				gomoku->setStone(getColor(), i, j);
				option = min(minMaxDepth, MAX_INT, maxBestOption, rules);
				gomoku->setStone(FREE, i, j);
				if (option > best) {
					best = option;
					rx = i;
					ry = j;
				}
				if (option > maxBestOption) {
					maxBestOption = option;
				}
//				DEBUG << "end\n";
			}
		}
	}
}

int MinMaxPlayer::max(int depth, int minBestOption, int maxBestOption, Rules &rules)
{
//	if (depth == 2) {
//		DEBUG << maxBestOption << " > " << minBestOption << "\n";
//	}
	if (depth <= 0) {
		return heuristic();
	}
	if (rules.checkEnd(*this)) {
		return heuristic();
	}
	int option;
	int best = MIN_INT;
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			if (gomoku->isFocus(i, j) && rules.canPutStone(*this, i, j)) {
				gomoku->setStone(getColor(), i, j);
				option = min(depth-1, minBestOption, maxBestOption, rules);
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

int MinMaxPlayer::min(int depth, int minBestOption, int maxBestOption, Rules &rules)
{
	if (depth <= 0) {
		return heuristic();
	}
	if (rules.checkEnd(*ennemy)) {
		return heuristic();
	}
	int option;
	int best = MAX_INT;
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			if (gomoku->isFocus(i, j) && rules.canPutStone(*this, i, j)) {
				gomoku->setStone(ennemy->getColor(), i, j);
				option = max(depth-1, minBestOption, maxBestOption, rules);
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
}

void MinMaxPlayer::play(Rules &rules, int &x, int &y) {
	x = -1;
	y = -1;
	startMinMax(x, y, rules);
	putStone(x, y);
}

int AI1::heuristic() {
//	return rand() % 1000;
	return gomoku->calculateWinPossibility(*this) - gomoku->calculateWinPossibility(*ennemy);
//	return gomoku->calculateWinPossibility(*this);
}
