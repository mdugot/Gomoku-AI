#include "randomPlayer.h"
#include "rules.h"

RandomPlayer::RandomPlayer() : Player()
{
}

RandomPlayer::~RandomPlayer()
{
}

int increment(int n, int max) {
	n++;
	if (n == max)
		n = 0;
	return n;
}

void RandomPlayer::play(Rules &rules) {
	int x = rand() % W;
	int y = rand() % H;
	int ox = x;
	int oy = y;
	do {
		y = oy;
		do {
			if (rules.canPutStone(*this, x, y)) {
				putStone(x, y);
				return;
			}
			y = increment(y, H);
		} while (y != oy);
		x = increment(x, W);
	} while (x != ox);
	failure("impossible to put stone on board");
}
