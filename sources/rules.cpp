#include "rules.h"

Rules::Rules() : turnCounter(0)
{
}

Rules::~Rules() {
}

bool Rules::win(Player &player) {
	int x = 0, y = 0;
	if (gomoku->fiveStoneLine(player.getColor(), x, y))
		return true;
	return false;
}

bool Rules::equality(Player &nextToPlay) {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (canPutStone(nextToPlay, i, j) == true)
				return false;
		}
	}
	return true;
}

void Rules::eat(Player &player) {
	(void)player;
}

End Rules::checkEnd(Player &nextToPlay) {
	if (win(gomoku->getWhitePlayer())) {
		DEBUG << LIGHT_GREY << HLL_RED << "White player win" << DEFAULT_COLOR << "\n";
		return WHITE_WIN;
	}
	if (win(gomoku->getBlackPlayer())) {
		DEBUG << DARK_BLACK << HLIGHT_RED << "Black player win" << DEFAULT_COLOR << "\n";
		return BLACK_WIN;
	}
	if (equality(nextToPlay)) {
		DEBUG << DARK_BLUE << HLIGHT_BLUE << "no winner" << DEFAULT_COLOR << "\n";
		return EQUALITY;
	}
	return NO_END;
}

void Rules::checkEat() {
	eat(gomoku->getBlackPlayer());
	eat(gomoku->getWhitePlayer());
}

