#include "gomoku.h"
#include "player.h"
#include "rules.h"
#include "interface.h"

Gomoku::Gomoku(Player &p1, Player &p2, Rules &rules, Interface &interface) : whitePlayer(p1), blackPlayer(p2), rules(rules), interface(interface), dleft(this), dright(this), vertical(this), horizontal(this)
{
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			board[i][j] = FREE;
			focus[i][j] = false;
		}
	}
	focus[GW/2][GH/2] = true;
	rules.setGomoku(this);
	whitePlayer.setGomoku(this);
	blackPlayer.setGomoku(this);
	interface.setGomoku(this);
	whitePlayer.setColor(WHITE);
	whitePlayer.setEnnemy(&blackPlayer);
	whitePlayer.setSpriteStone(sf::Color::White);
	blackPlayer.setColor(BLACK);
	blackPlayer.setSpriteStone(sf::Color::Black);
	blackPlayer.setEnnemy(&whitePlayer);
	currentPlayer = &blackPlayer;
}

Gomoku::~Gomoku()
{
}

void Gomoku::start() {
	//interface.start();
	currentPlayer = &blackPlayer;
	otherPlayer = &whitePlayer;
	int x, y;
	while (!rules.checkEnd(*currentPlayer)/* || interface._window.isOpen()*/) {
       // interface.checkEvent();
	 	DEBUG << "\n";
		currentPlayer->play(rules, x, y);
		otherPlayer->observe(rules, x, y);
//		if (rules.turnCounter < 30) {
			printBoard(x, y);
			DEBUG << "win possibility : " << calculateWinPossibility(*currentPlayer) << "\n";
//		}
		if (currentPlayer == &blackPlayer) {
			currentPlayer = &whitePlayer;
			otherPlayer = &blackPlayer;
		} else {
			currentPlayer = &blackPlayer;
			otherPlayer = &whitePlayer;
		}
		rules.turnCounter += 1;
        //interface.update();

//		std::string input = "";
//		std::cout << "PRESS ENTER TO CONTINUE\n";
//		std::getline(std::cin, input);
	}
	printBoard();
}

Stone Gomoku::getStone(int x, int y) {
	 if (x < 0 || y < 0 || x >= GW || y >= GH)
	 	return OUT_LIMIT;
	return board[x][y];
}

void Gomoku::updateFocus(int x, int y) {
	for (int i = x-FOCUS; i <= x+FOCUS ; i++) {
		for (int j = y-FOCUS; j <= y+FOCUS ; j++) {
			if (i >= 0 && j >= 0 && i < GW && j < GH)
				focus[i][j] = true;
		}
	}
}

void Gomoku::printStone(int i, int j, int lastX, int lastY) {
	if (board[i][j] == WHITE) {
		DEBUG << ((lastX == i && lastY == j) ? GREEN : DEFAULT_COLOR) << HLL_GREY << "O" << DEFAULT_COLOR;
	} else if (board[i][j] == BLACK) {
		DEBUG << ((lastX == i && lastY == j) ? RED : DARK_BLACK) << HLIGHT_GREY << "X" << DEFAULT_COLOR;
	} else {
		if (focus[i][j]) {
			DEBUG << ".";
		} else {
			DEBUG << "#";
		}
	}
}

void Gomoku::printBoard(int lastX, int lastY) {
	DEBUG << "\n";
	for (int j = 0; j < GH; j++) {
		for (int i = 0; i < GW; i++) {
			printStone(i, j, lastX, lastY);
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
	if (getStone(x, y) != color)
		return false;
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
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			if (checkLine(color, i, j)) {
				x = i;
				y = j;
				return true;
			}
		}
	}
	return false;
}

int Gomoku::calculateWinPossibility(Player &player, BoardIterator &iterator, bool &win) {
	bool newLine = false;
	PositionAnalyse analyse = OTHER;
	int minLength = 5;
	int length = 0;
	int temporaryAlignementPossibility = -1;
	int gap = 0;
	int result = 0;

	if (win)
		return result;
	iterator.reset();
	while ((analyse = iterator(player, newLine)) != ITERATION_END) {
		if (isFocus(iterator.getX(), iterator.getY())) {
			if (newLine
				|| (gap >= minLength - 1 && temporaryAlignementPossibility >= 0)
				|| analyse == ENNEMY_STONE) {
				if (length >= minLength && temporaryAlignementPossibility > 0) {
				//	DEBUG << "add to result : " << temporaryAlignementPossibility <<  " - " << iterator.getX() << "/" << iterator.getY() << "\n";
					result += temporaryAlignementPossibility;
					if (temporaryAlignementPossibility >= 4) {
						win = true;
						return result;
					}
				}
				temporaryAlignementPossibility = -1;
				length = 0;
				gap = 0;
			}
			if (analyse == MY_STONE) {
				gap = 0;
				length += 1;
				temporaryAlignementPossibility += 1;
			}
			else if (analyse == CAN_PUT_STONE) {
				gap += 1;
				length += 1;
			}
		}
	}
	return result;
}

int Gomoku::calculateWinPossibility(Player &player) {
	int r = 0;
	bool win = false;
	r += calculateWinPossibility(player, vertical, win);
	r += calculateWinPossibility(player, horizontal, win);
	r += calculateWinPossibility(player, dleft, win);
	r += calculateWinPossibility(player, dright, win);
	if (win)
		return MAX_INT;
	return r;
}
