# ifndef PRORULES_H
# define RULESTEST_H

#include "rules.h"

class ProRules : public Rules
{
	private:

	public:

		ProRules();
		~ProRules();


		virtual bool	canPutStone(HeuristicBoard *h, int x, int y);
        virtual Rules	*copy();
		virtual void	specificRules();
};

# endif