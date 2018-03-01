#include "rules.h"

Rules::Rules() : turnCounter(0)
{
}

Rules::~Rules() {
}

bool Rules::win(Player &player) {
	int x = 0, y = 0; //pourra être utile pour s'assurer de l'endroit de la victoire et faire une animation graphique
	if (gomoku->fiveStoneLine(player.getColor(), x, y))
		return true;
	else if (player.getNbCapture() == (int)NB_CAPTURE_TO_WIN)
		return true;
	return false;
}

bool Rules::equality(Player &nextToPlay) {
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			if (canPutStone(nextToPlay, i, j) == true)
				return false;
		}
	}
	return true;
}

End Rules::checkEnd(Player &nextToPlay) {
	if (win(gomoku->getWhitePlayer())) {
		DEBUG << LIGHT_GREY << HLL_RED << "White player win" << DEFAULT_COLOR << "\n";
		return WHITE_WIN;
	}
	else if (win(gomoku->getBlackPlayer())) {
		DEBUG << DARK_BLACK << HLIGHT_RED << "Black player win" << DEFAULT_COLOR << "\n";
		return BLACK_WIN;
	}
	else if (equality(nextToPlay)) {
		DEBUG << DARK_BLUE << HLIGHT_BLUE << "no winner" << DEFAULT_COLOR << "\n";
		return EQUALITY;
	}
	return NO_END;
}

void	Rules::noDoubleThrees(Player &current) {
	//A appliquer sur tous le board ou juste au moment du coup joué ???
	gomoku->checkAlignThrees(current);
}