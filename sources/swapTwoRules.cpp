#include "swapTwoRules.h"

SwapTwoRules::SwapTwoRules() : Rules()
{
}

SwapTwoRules::~SwapTwoRules()
{
}

Rules *SwapTwoRules::copy() {
	SwapTwoRules *cpy = new SwapTwoRules();
	cpy->setGomoku(gomoku);
	cpy->setTurnCounter(turnCounter);
    DEBUG << "SwapTwoRules";
	return cpy;
}

bool SwapTwoRules::canPutStone(HeuristicBoard *heuristic, int x, int y) {
    DEBUG << "SwapTwoRules";
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}

void	SwapTwoRules::specificRules(Interface &interface) {
	(void)interface;
	if (turnCounter > 3)
		return;
	else if (turnCounter == 1)
		DEBUG << "TEST SPECIFIC SWAP TWO RULES";
	return;
}