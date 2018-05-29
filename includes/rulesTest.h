# ifndef RULESTEST_H
# define RULESTEST_H

#include "rules.h"

class RulesTest : public Rules
{
	private:

	public:

		RulesTest();
		~RulesTest();


		virtual bool canPutStone(HeuristicBoard *h, int x, int y);
        virtual Rules *copy();
};

# endif