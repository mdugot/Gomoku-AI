#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "utils.h"
#include "player.h"

class RandomPlayer : public Player
{
	private:

	
	public:

		RandomPlayer();
		~RandomPlayer();

		virtual void play(Rules &rules, Interface &i);
};

#endif
