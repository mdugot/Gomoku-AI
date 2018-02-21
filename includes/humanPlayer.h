#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "utils.h"

#include "player.h"

class HumanPlayer : public Player
{
	private:
	
	public:

		HumanPlayer();
		~HumanPlayer();

		virtual void play(Rules &rules, Interface &i);
};

#endif