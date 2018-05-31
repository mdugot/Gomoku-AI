# ifndef SWAPRULES_H
# define SWAPRULES_H

#include "rules.h"

class SwapRules : public Rules
{
	private:

	public:

		SwapRules();
		~SwapRules();


		virtual bool canPutStone(HeuristicBoard *h, int x, int y);
        virtual Rules *copy();
		virtual void specificRules();
};

# endif