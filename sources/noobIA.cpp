#include "noobIA.h"
#include "rules.h"
#include "interface.h"

NoobIA::NoobIA() : Player()
{
}

NoobIA::~NoobIA()
{
}

void NoobIA::play(Rules &rules, Interface &i) {
	while (!this->played)
	{
		int x = rand() % GW;
		int y = rand() % GH;
		if (rules.canPutStone(*this, x, y)) {
			this->putStone(x, y);
			i.putStone(*(this->stoneSprite), i.getCoordBoard(x,y).x, i.getCoordBoard(x,y).y);
			this->played = true;
		}
	}
	return;
}