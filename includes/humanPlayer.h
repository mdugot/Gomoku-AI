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

		//virtual Vector2<int> play(Rules &rules, Vector2<int>) = 0;
		virtual void play(Rules &rules, Interface &i);
};

#endif