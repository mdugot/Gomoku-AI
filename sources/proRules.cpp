#include "proRules.h"

ProRules::ProRules() : Rules()
{
}

ProRules::~ProRules()
{
}

Rules *ProRules::copy() {
	ProRules *cpy = new ProRules();
	cpy->setGomoku(gomoku);
	cpy->setTurnCounter(turnCounter);
    DEBUG << "ProRules";
	return cpy;
}

bool ProRules::canPutStone(HeuristicBoard *heuristic, int x, int y) {
    DEBUG << "ProRules";
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}

void	ProRules::specificRules() {
	if (turnCounter > 3)
		return;
	else if (turnCounter == 1)
		DEBUG << "TEST SPECIFIC PRO RULES";
	return;
}