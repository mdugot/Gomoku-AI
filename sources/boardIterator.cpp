#include "boardIterator.h"
#include "gomoku.h"
#include "player.h"
#include "rules.h"


BoardIterator::BoardIterator(Gomoku *gomoku) {
	this->gomoku = gomoku;
}

BoardIterator::~BoardIterator() {
}

void BoardIterator::reset() {
	x = ox;
	y = oy;
}

VerticalIterator::VerticalIterator(Gomoku *gomoku) : BoardIterator(gomoku)
{
	ox = 0;
	oy = 0;
}

VerticalIterator::~VerticalIterator() {
}

HorizontalIterator::HorizontalIterator(Gomoku *gomoku) : BoardIterator(gomoku)
{
	ox = 0;
	oy = 0;
}

HorizontalIterator::~HorizontalIterator() {
}

DLeftIterator::DLeftIterator(Gomoku *gomoku) : BoardIterator(gomoku)
{
	ox = 4;
	oy = 0;
}

DLeftIterator::~DLeftIterator() {
}

DRightIterator::DRightIterator(Gomoku *gomoku) : BoardIterator(gomoku)
{
	ox = GW - 5;
	oy = 0;
}

DRightIterator::~DRightIterator() {
}

PositionAnalyse BoardIterator::analyse(Player &player) {
	Stone actual = gomoku->getStone(x, y);
	if (actual == player.getColor())
		return MY_STONE;
	if (actual != FREE)
		return ENNEMY_STONE;
	if (gomoku->getRules().canPutStone(player, x, y))
		return CAN_PUT_STONE;
	return OTHER;
	
}

PositionAnalyse VerticalIterator::operator()(Player &player, bool &newLine) {
	y += 1;
	newLine = false;
	if (y >= GH) {
		y = 0;
		x++;
		newLine = true;
		if (x >= GW)
			return ITERATION_END;
	}
	return analyse(player);
}

PositionAnalyse HorizontalIterator::operator()(Player &player, bool &newLine) {
	x += 1;
	newLine = false;
	if (x >= GW) {
		x = 0;
		y++;
		newLine = true;
		if (y >= GH)
			return ITERATION_END;
	}
	return analyse(player);
}

PositionAnalyse DLeftIterator::operator()(Player &player, bool &newLine) {
	x -= 1;
	y += 1;
	newLine = false;
	if (x < 0 || y >= GH) {
		x = x + y + 1;
		y = 0;
		newLine = true;
		if (x >= GW) {
			y = x - GW + 1;
			x = GW - 1;
			if ( y >= GH - 5)
				return ITERATION_END;
		}
	}
	return analyse(player);
}

PositionAnalyse DRightIterator::operator()(Player &player, bool &newLine) {
	x += 1;
	y += 1;
	newLine = false;
	if (x >= GW || y >= GH) {
		x = x - y - 1;
		y = 0;
		newLine = true;
		if (x < 0) {
			y = -x;
			x = 0;
			if ( y >= GH - 5)
				return ITERATION_END;
		}
	}
	return analyse(player);
}
