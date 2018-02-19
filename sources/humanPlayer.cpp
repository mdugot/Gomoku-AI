#include "humanPlayer.h"
#include "rules.h"
#include "interface.h"

HumanPlayer::HumanPlayer() : Player()
{
}

HumanPlayer::~HumanPlayer()
{
}


void HumanPlayer::play(Rules &rules, Interface &i) {
	(void)rules;
	while (!this->played)
	{
		i.checkEvent(*this);
		//if (rules.canPutStone(*this, v.x, v.y)) {
		//this->putStone(v.x, v.y);
	//return v;
	}
	return;
}
