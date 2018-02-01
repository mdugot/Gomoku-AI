#ifndef RULES_H
#define RULES_H

#include "player.h"
#include "gomoku.h"

class Gomoku;

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
		bool win(Player &player);
		bool equality();
		void eat(Player &player);
	
	public:

		Rules();
		~Rules();

		virtual bool canPutStone(Player &player, int x, int y) = 0;

		End checkEnd();
		void checkEat();
};


#endif

