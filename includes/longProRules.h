# ifndef LONGPRORULES_H
# define LONGPRORULES_H

#include "rules.h"

class LongProRules : public Rules
{
	private:

	public:

		LongProRules();
		~LongProRules();


		virtual bool canPutStone(HeuristicBoard *h, int x, int y);
        virtual Rules *copy();
		virtual void initStartingFocus();
		virtual void specificRules(Interface &interface);
};

# endif
