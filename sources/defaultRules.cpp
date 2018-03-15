#include "defaultRules.h"

DefaultRules::DefaultRules() : Rules()
{
}

DefaultRules::~DefaultRules()
{
}

bool DefaultRules::canPutStone(Player &player, int x, int y) {
	if (player.getMyHeuristic()->checkDoubleFreeThree((unsigned char)x, (unsigned char)y))
		return false;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}
