#include "humanPlayer.h"
#include "interface.h"
#include "rules.h"

HumanPlayer::HumanPlayer() : Player()
{
	this->played = false;
}

HumanPlayer::~HumanPlayer()
{
}


void HumanPlayer::play(Rules &rules, Interface &i) {
	(void)rules;
	while (!this->played) {
		i->checkEvent(*this);
	}
	this->played = false;
}
