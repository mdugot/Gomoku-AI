#include "noobIA.h"
#include "rules.h"
#include "interface.h"

NoobIA::NoobIA() : Player()
{
	DEBUG << "\nNEW NOOBIA PLAYER\n";
}

NoobIA::~NoobIA()
{
	DEBUG << "\nBYE NOOBIA\n";
}

void NoobIA::play(Rules &rules, Interface &i) {
	(void)i;
	while (!this->played)
	{
		int x = rand() % GW;
		int y = rand() % GH;
		if (rules.canPutStone(*this, x, y)) {
			setCoordPlayed(x, y);
			this->putStone(x, y);
			this->played = true;
		}
	}
	return;
}
