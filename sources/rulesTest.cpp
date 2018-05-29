#include "rulesTest.h"

RulesTest::RulesTest() : Rules()
{
}

RulesTest::~RulesTest()
{
}

Rules *RulesTest::copy() {
	RulesTest *cpy = new RulesTest();
	cpy->setGomoku(gomoku);
	cpy->setTurnCounter(turnCounter);
    DEBUG << "RULESTEST";
	return cpy;
}

bool RulesTest::canPutStone(HeuristicBoard *heuristic, int x, int y) {
    DEBUG << "RULESTEST";
	if (heuristic->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}