#include "swapRules.h"

SwapRules::SwapRules() : 	Rules()
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
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}

void	SwapRules::specificRules(Interface &interface) {
	if (turnCounter > 4)
		return;
	else if (turnCounter == 0)
		interface.setRulesText("Put 3 first stone,\nwhere you want.", BRULESX, BRULESY);
	else if (turnCounter == 1) {
		interface.setRulesText("Put 3 first stone,\nwhere you want.", BRULESX, BRULESY);
		gomoku->setCurrentPlayer(gomoku->getCurrentPlayer()->getEnemy());
		gomoku->getCurrentPlayer()->setColor(WHITE);
		gomoku->getCurrentPlayer()->setSpriteStone(interface.getSpriteWhiteStone());
	}
	else if (turnCounter == 2){
		interface.setRulesText("Put 3 first stone,\nwhere you want.", BRULESX, BRULESY);
		gomoku->setCurrentPlayer(gomoku->getCurrentPlayer()->getEnemy());
		gomoku->getCurrentPlayer()->setColor(BLACK);
		gomoku->getCurrentPlayer()->setSpriteStone(interface.getSpriteBlackStone());
	}
	else if (turnCounter == 3){
		DEBUG << "MISSING implementation SWAP PLAYER IF HUMAN OR IF IA";
		interface.setRulesText("CHOOSE :\n-play white now\n-play black after\n...and forever", WRULESX, WRULESY);
	}
	else if (turnCounter == 4)
		interface.setRulesText("No specific rules", BRULESX, BRULESY);
	return;
}
