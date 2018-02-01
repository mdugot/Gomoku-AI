#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "player.h"

class RandomPlayer : public Player
{
	private:

	
	public:

		RandomPlayer();
		~RandomPlayer();

		virtual void play(Rules &rules);
};


#endif

