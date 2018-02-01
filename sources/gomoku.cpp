#include "gomoku.h"
#include "player.h"
#include "rules.h"

Gomoku::Gomoku(Player &p1, Player &p2, Rules &rules) : whitePlayer(p1), blackPlayer(p2), rules(rules)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			board[i][j] = FREE;
		}
	}
	rules.setGomoku(this);
	whitePlayer.setGomoku(this);
	blackPlayer.setGomoku(this);
	whitePlayer.setColor(WHITE);
	blackPlayer.setColor(BLACK);
}

Gomoku::~Gomoku()
{
}

void Gomoku::start() {
	Player *currentPlayer = &blackPlayer;
	while (!rules.checkEnd(*currentPlayer)) {
		currentPlayer->play(rules);
		if (currentPlayer == &blackPlayer)
			currentPlayer = &whitePlayer;
		else
			currentPlayer = &blackPlayer;
		rules.turnCounter += 1;
	}
	printBoard();
}

Stone Gomoku::getStone(int x, int y) {
	 if (x < 0 || y < 0 || x >= W || y >= H)
	 	return OUT_LIMIT;
	return board[x][y];
}

void Gomoku::printBoard() {
	DEBUG << "\n";
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (board[i][j] == WHITE) {
				DEBUG << DEFAULT_COLOR << HLL_GREY << "O" << DEFAULT_COLOR;
			} else if (board[i][j] == BLACK) {
				DEBUG << DARK_BLACK << HLIGHT_GREY << "X" << DEFAULT_COLOR;
			} else {
				DEBUG << ".";
			}
		}
		DEBUG << "\n";
	}
}

bool Gomoku::horizontalLine(Stone color, int x, int y) {
	for (int i = x; i < (x + 5); i++) {
		if (getStone(i, y) != color) {
			return false;
		}
	}
	return true;
}

bool Gomoku::verticalLine(Stone color, int x, int y) {
	for (int i = y; i < (y + 5); i++) {
		if (getStone(x, i) != color)
			return false;
	}
	return true;
}

bool Gomoku::rightDiagonal(Stone color, int x, int y) {
	for (int i = 0; i < 5; i++) {
		if (getStone(x + i, y + i) != color)
			return false;
	}
	return true;
}

bool Gomoku::leftDiagonal(Stone color, int x, int y) {
	for (int i = 0; i < 5; i++) {
		if (getStone(x - i, y + i) != color)
			return false;
	}
	return true;
}

bool Gomoku::checkLine(Stone color, int x, int y) {
	if (horizontalLine(color, x, y))
		return true;
	if (verticalLine(color, x, y))
		return true;
	if (rightDiagonal(color, x, y))
		return true;
	if (leftDiagonal(color, x, y))
		return true;
	return false;
}

bool Gomoku::fiveStoneLine(Stone color, int &x, int &y) {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (checkLine(color, i, j)) {
				x = i;
				y = j;
				return true;
			}
		}
	}
	return false;
}