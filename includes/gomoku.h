#ifndef GOMOKU_H
#define GOMOKU_H

#include "utils.h"
#include "colors.h"

#define W 19
#define H 19

class Player;
class Rules;

typedef enum Stone {
	BLACK = 1, WHITE = 2, FREE = 0, OUT_LIMIT = -1
} Stone;

class Gomoku
{
	private:
		
		Player &whitePlayer;
		Player &blackPlayer;
		Rules &rules;
		Stone board[W][H];

		bool checkLine(Stone color, int x, int y);
		bool leftDiagonal(Stone color, int x, int y);
		bool rightDiagonal(Stone color, int x, int y);
		bool verticalLine(Stone color, int x, int y);
		bool horizontalLine(Stone color, int x, int y);

	
	public:

		Gomoku(Player& p1, Player& p2, Rules& rules);
		~Gomoku();

		inline Player &getWhitePlayer() {return whitePlayer;}
		inline Player &getBlackPlayer() {return blackPlayer;}
		inline Rules &getRules() {return rules;}
		Stone getStone(int x, int y);
		inline void setStone(Stone stone, int x, int y) {board[x][y] = stone;}

		bool fiveStoneLine(Stone color, int &x, int &y);

		void printBoard();
		void start();
};


#endif
