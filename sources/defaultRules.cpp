#include "defaultRules.h"

DefaultRules::DefaultRules() : Rules()
{
}

DefaultRules::~DefaultRules()
{
}

bool DefaultRules::canPutStone(Player &player, int x, int y) {
	(void)player;
	if (gomoku->getStone(x, y) == FREE)
		return true;
	return false;
}
