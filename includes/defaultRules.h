#ifndef DEFAULTRULES_H
#define DEFAULTRULES_H

#include "rules.h"

class DefaultRules : public Rules
{
	private:

	public:

		DefaultRules();
		~DefaultRules();


		virtual bool canPutStone(Player &player, int x, int y);
};


#endif
