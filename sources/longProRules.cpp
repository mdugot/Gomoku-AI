#include "longProRules.h"

LongProRules::LongProRules() : Rules()
{
}

LongProRules::~LongProRules()
{
}

Rules *LongProRules::copy() {
	LongProRules *cpy = new LongProRules();
	cpy->setGomoku(gomoku);
	cpy->setTurnCounter(turnCounter);
    DEBUG << "LongProRules";
	return cpy;
}

bool LongProRules::canPutStone(HeuristicBoard *heuristic, int x, int y) {
    DEBUG << "LongProRules";
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}

void	LongProRules::specificRules(Interface &interface) {
	(void)interface;
	if (turnCounter > 3)
		return;
	else if (turnCounter == 1)
		DEBUG << "TEST SPECIFIC RULES";
	return;
}