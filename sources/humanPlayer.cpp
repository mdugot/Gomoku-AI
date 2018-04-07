#include "humanPlayer.h"
#include "rules.h"
#include "interface.h"

HumanPlayer::HumanPlayer() : Player()
{
	DEBUG << "NEW HUMAN\n";
}

HumanPlayer::~HumanPlayer()
{
	DEBUG << "BYE HUMAN\n";
}


void HumanPlayer::play(Rules &rules, Interface &i) {
	(void)rules;
	while (!this->played)
	{
		i.checkEvent(this);
	}
    putStone(coordPlayed.x, coordPlayed.y);
	return;
}
