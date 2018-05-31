#include "swapRules.h"

SwapRules::SwapRules() : Rules()
{
}

SwapRules::~SwapRules()
{
}

Rules *SwapRules::copy() {
	SwapRules *cpy = new SwapRules();
	cpy->setGomoku(gomoku);
	cpy->setTurnCounter(turnCounter);
    DEBUG << "SwapRules";
	return cpy;
}

bool SwapRules::canPutStone(HeuristicBoard *heuristic, int x, int y) {
    DEBUG << "SwapRules";
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}

void	SwapRules::specificRules(Interface &interface) {
	(void)interface;
	if (turnCounter > 3)
		return;
	else if (turnCounter == 0) // TEST
		DEBUG << "TEST SPECIFIC SWAP RULES";
	return;
}