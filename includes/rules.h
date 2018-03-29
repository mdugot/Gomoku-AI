#ifndef RULES_H
#define RULES_H

#include "gomoku.h"
#include "player.h"

#define NB_CAPTURE_TO_WIN 10

typedef enum End {
	BLACK_WIN = 1, WHITE_WIN = 2, EQUALITY = 3, NO_END = 0
} End;

class Rules
{
	friend class Gomoku;

	protected:

		unsigned int turnCounter;
		Gomoku *gomoku;
		
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		bool win(Player &player, bool avoidable);
		bool equality(Player &nextToPlay);
		bool canAvoidDefeat(Player *player, Player *ennemy);
		End playerWon(Player &player);
	
	public:

		Rules();
		~Rules();

		virtual bool canPutStone(Player &player, int x, int y) = 0;

		End checkEnd(Player &nextToPlay);
};


#endif

