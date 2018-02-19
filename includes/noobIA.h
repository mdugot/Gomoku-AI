#ifndef NOOBIA_H
#define NOOBIA_H

#include "utils.h"
#include "player.h"

class NoobIA : public Player
{
	private:

	
	public:

		NoobIA();
		~NoobIA();

		virtual void play(Rules &rules, Interface &i);
};

#endif