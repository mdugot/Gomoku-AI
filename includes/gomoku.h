#ifndef GOMOKU_H
#define GOMOKU_H

#include "utils.h"
#include "colors.h"
#include "boardIterator.h"

#define GW 19
#define GH 19
#define FOCUS 4

class Player;
class Rules;
class Interface;

typedef enum Stone {
	BLACK = 1, WHITE = 2, FREE = 0, OUT_LIMIT = -1
} Stone;

class Gomoku
{
	private:
		
		Player &whitePlayer;
		Player &blackPlayer;
		Player *currentPlayer;
		Player *otherPlayer;

		Rules &rules;
		Interface &interface;
		Stone board[GW][GH];
		bool focus[GW][GH];

		DLeftIterator dleft;
		DRightIterator dright;
		VerticalIterator vertical;
		HorizontalIterator horizontal;

		bool checkLine(Stone color, int x, int y);
		bool leftDiagonal(Stone color, int x, int y);
		bool rightDiagonal(Stone color, int x, int y);
		bool verticalLine(Stone color, int x, int y);
		bool horizontalLine(Stone color, int x, int y);
		int calculateWinPossibility(Player &player, BoardIterator &iterator, bool &win);

	
	public:

		Gomoku(Player& p1, Player& p2, Rules& rules, Interface& interface);
		~Gomoku();

		inline Player &getWhitePlayer() {return whitePlayer;}
		inline Player &getBlackPlayer() {return blackPlayer;}
		inline Player *getCurrentPlayer() {return currentPlayer;}
		inline Rules &getRules() {return rules;}
		inline Stone** getBoard() {return (Stone**)board;}
		inline Interface &getInterface() {return interface;}
		Stone getStone(int x, int y);
		inline void setStone(Stone stone, int x, int y) {board[x][y] = stone;}
		inline bool isFocus(int x, int y) {return focus[x][y];}
		void updateFocus(int x, int j);

		bool fiveStoneLine(Stone color, int &x, int &y);
		int calculateWinPossibility(Player &player);

		void printBoard();
		void start();
};


#endif
