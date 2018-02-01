#include "rules.h"

Rules::Rules() : turnCounter(0)
{
}

Rules::~Rules() {
}

bool Rules::win(Player &player) {
	(void)player;
	return false;
}

bool Rules::equality() {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (gomoku->getStone(i, j) == FREE)
				return false;
		}
	}
	return true;
}

void Rules::eat(Player &player) {
	(void)player;
}

End Rules::checkEnd() {
	if (win(gomoku->getWhitePlayer())) {
		DEBUG << HLIGHT_BLACK << "White player win" << DEFAULT_COLOR << "\n";
		return WHITE_WIN;
	}
	if (win(gomoku->getBlackPlayer())) {
		DEBUG << HLIGHT_BLACK << "Black player win" << DEFAULT_COLOR << "\n";
		return BLACK_WIN;
	}
	if (equality()) {
		DEBUG << "no winner" << DEFAULT_COLOR << "\n";
		return EQUALITY;
	}
	return NO_END;
}

void Rules::checkEat() {
	eat(gomoku->getBlackPlayer());
	eat(gomoku->getWhitePlayer());
}
