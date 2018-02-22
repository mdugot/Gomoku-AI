#include "player.h"
#include "gomoku.h"

Player::Player() : eatenStones(0)
{
}

Player::~Player() {
}

void Player::putStone(int x, int y) {
	if (stoneColor == WHITE) {
		DEBUG << DEFAULT_COLOR << HLL_GREY << "White player put stone in " << x << "/" << y << DEFAULT_COLOR << "\n";
	} else {
		DEBUG << DARK_BLACK << HLIGHT_GREY << "Black player put stone in " << x << "/" << y << DEFAULT_COLOR << "\n";
	}
	gomoku->setStone(stoneColor, x, y);
	gomoku->updateFocus(x, y);
}
