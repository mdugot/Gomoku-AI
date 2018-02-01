#ifndef GOMOKU_H
#define GOMOKU_H

#include "utils.h"
#include "colors.h"

#define W 19
#define H 19

class Player;
class Rules;

typedef enum Stone {
	BLACK = 1, WHITE = 2, FREE = 0
} Stone;

class Gomoku
{
	private:
		
		Player &whitePlayer;
		Player &blackPlayer;
		Rules &rules;
		Stone board[W][H];


	
	public:

		Gomoku(Player& p1, Player& p2, Rules& rules);
		~Gomoku();

		inline Player &getWhitePlayer() {return whitePlayer;}
		inline Player &getBlackPlayer() {return blackPlayer;}
		inline Rules &getRules() {return rules;}
		inline Stone getStone(int x, int y) {return board[x][y];}
		inline void setStone(Stone stone, int x, int y) {board[x][y] = stone;}


		void start();
};


#endif
