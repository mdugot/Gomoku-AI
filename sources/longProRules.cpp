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
	if (turnCounter == 0){
		if (x == 9 && y == 9)
			return true;
		else
			return false;
	}
	if (turnCounter == 2){
		if ((x <= 12 && x >= 6 && y <= 12 && y >= 6))
			return false;
	}
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}

void	LongProRules::specificRules(Interface &interface) {
	if (turnCounter > 3)
		return;
	else if (turnCounter <= 2){
		interface.setShapeInDrawList(interface.getPtrSevenBySevenRect());
	}
	if (turnCounter == 0)
		interface.setRulesText("Play in Middle = H8.", BRULESX, BRULESY);
	else if (turnCounter == 1)
		interface.setRulesText("Play where you want", WRULESX, WRULESY);
	else if (turnCounter == 2)
		interface.setRulesText("Play outside of square", BRULESX, BRULESY);
	else if (turnCounter == 3)
		interface.setRulesText("No specific rules", WRULESX, WRULESY);
	return;
}