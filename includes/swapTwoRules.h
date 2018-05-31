# ifndef SWAPTWORULES_H
# define SWAPTWORULES_H

#include "rules.h"

class SwapTwoRules : public Rules
{
	private:

	public:

		SwapTwoRules();
		~SwapTwoRules();


		virtual bool canPutStone(HeuristicBoard *h, int x, int y);
        virtual Rules *copy();
		virtual void specificRules();
};

# endif