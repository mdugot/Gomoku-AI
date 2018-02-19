#include "gomoku.h"
#include "player.h"

Player::Player() : eatenStones(0)
{
	played = false;
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
}
