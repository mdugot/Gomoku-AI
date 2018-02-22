#include "gomoku.h"
#include "player.h"
#include "rules.h"
#include "interface.h"

using namespace sf;

Gomoku::Gomoku(Player &p1, Player &p2, Rules &rules, Interface &interface) : whitePlayer(p1), blackPlayer(p2), rules(rules), interface(interface)
{
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
			board[i][j] = FREE;
		}
	}
	rules.setGomoku(this);
	whitePlayer.setGomoku(this);
	blackPlayer.setGomoku(this);
	interface.setGomoku(this);
	whitePlayer.setMyColor(WHITE);
	blackPlayer.setMyColor(BLACK);
	currentPlayer = &blackPlayer;
}

Gomoku::~Gomoku()
{
}

void Gomoku::start() {
	whitePlayer.setSpriteStone(&(interface._whiteStone));
	blackPlayer.setSpriteStone(&(interface._blackStone));
	//whitePlayer.canteen = interface.whiteCanteen;
	//blackPlayer.canteen = interface.blackCanteen;
	currentPlayer = &blackPlayer;
	interface.setState(GAME);
	while (!rules.checkEnd(*currentPlayer) &&
		interface._window.isOpen()) {
        interface.update();
		while (!currentPlayer->played) {
			currentPlayer->play(rules, interface);
		}
		currentPlayer->played = false;
		if (currentPlayer == &blackPlayer) {
			checkCapture(*currentPlayer, currentPlayer->coordPlayed.x, currentPlayer->coordPlayed.y, whitePlayer);
			currentPlayer = &whitePlayer;
		}
		else {
			checkCapture(*currentPlayer, currentPlayer->coordPlayed.x, currentPlayer->coordPlayed.y, blackPlayer);
			currentPlayer = &blackPlayer;
		}
		interface.checkEvent(*currentPlayer);
		rules.turnCounter += 1;
	}
	printBoard();
}

Stone Gomoku::getStone(int x, int y) {
	 if (x < 0 || y < 0 || x >= GW || y >= GH)
	 	return OUT_LIMIT;
	return board[x][y];
}

void Gomoku::printBoard() {
	DEBUG << "\n";
	for (int i = 0; i < GW; i++) {
		for (int j = 0; j < GH; j++) {
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

bool Gomoku::checkCapture(Player &current, int x, int y, Player &enemy)
{
	if (checkLeft(current, x, y, enemy) ||
		checkRight(current, x, y, enemy) ||
		checkUp(current, x, y, enemy) ||
		checkDown(current, x, y, enemy) ||
		checkUpLeft(current, x, y, enemy) ||
		checkDownLeft(current, x, y, enemy) ||
		checkUpRight(current, x, y, enemy) ||
		checkUpLeft(current, x, y, enemy))
		return (true);
	return (false);
}

void Gomoku::capture(Player &current, Sprite *spriteEnemy, int x1, int y1, int x2, int y2) {
	current.nbCapture += 2;
	(void)current;
	(void)spriteEnemy;
	setStone(FREE, x1, y1);
	setStone(FREE, x2, y2);
			DEBUG << "CAPTURE = " << current.nbCapture << " " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
	interface.capture(current, spriteEnemy, x1, y1, x2, y2); // ajoute 2 stones de la couleur enemy du current dans sa zone de capture, pour cela check le nb de capture et put des stones au bon endroit.
}

bool Gomoku::checkBetween(Stone colorEnemy, int x1, int y1, int x2, int y2) {
	return (getStone(x1, y1) == colorEnemy && getStone(x2,y2) == colorEnemy);
}

bool Gomoku::checkLeft(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed - 3, yPlayed) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed - 2, yPlayed, xPlayed - 1, yPlayed)) {
			capture(current, enemy.getSpriteStone(), xPlayed - 2, yPlayed, xPlayed - 1, yPlayed);
			DEBUG << "CAPTURE LEFT!!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkRight(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed + 3, yPlayed) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed + 2, yPlayed, xPlayed + 1, yPlayed)) {
			capture(current, enemy.getSpriteStone(), xPlayed + 2, yPlayed, xPlayed + 1, yPlayed);
			DEBUG << "CAPTURE RIGHT!!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkUp(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed, yPlayed - 3) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed, yPlayed - 2, xPlayed, yPlayed - 1)) {
			capture(current, enemy.getSpriteStone(), xPlayed, yPlayed - 2, xPlayed, yPlayed - 1);
			DEBUG << "CAPTURE UP!!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkDown(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed, yPlayed + 3) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed, yPlayed + 2, xPlayed, yPlayed + 1)) {
			capture(current, enemy.getSpriteStone(), xPlayed, yPlayed + 2, xPlayed, yPlayed + 1);
			DEBUG << "CAPTUREDOWN !!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkUpLeft(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed - 3, yPlayed - 3) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed - 2, yPlayed - 2, xPlayed - 1, yPlayed - 1)) {
			capture(current, enemy.getSpriteStone(), xPlayed - 2, yPlayed - 2, xPlayed - 1, yPlayed - 1);
			DEBUG << "CAPTUREUPLEFT !!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkDownLeft(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed - 3, yPlayed + 3) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed - 2, yPlayed + 2, xPlayed - 1, yPlayed + 1)) {
			capture(current, enemy.getSpriteStone(), xPlayed - 2, yPlayed + 2, xPlayed - 1, yPlayed + 1);
			DEBUG << "CAPTUREDOWNLEFT !!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkUpRight(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed + 3, yPlayed - 3) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed + 2, yPlayed - 2, xPlayed + 1, yPlayed - 1)) {
			capture(current, enemy.getSpriteStone(), xPlayed + 2, yPlayed - 2, xPlayed + 1, yPlayed - 1);
			DEBUG << "CAPTUREUPRIGHT !!!!!!!!!";
			return (true);
		}
	}
	return (false);
}

bool Gomoku::checkDownRight(Player &current, int xPlayed, int yPlayed, Player &enemy) {
	if (getStone(xPlayed + 3, yPlayed + 3) == current.getColor()) {
		if (checkBetween(enemy.getColor(), xPlayed + 2, yPlayed + 2, xPlayed + 1, yPlayed + 1)) {
			capture(current, enemy.getSpriteStone(), xPlayed + 2, yPlayed + 2, xPlayed + 1, yPlayed + 1);
			DEBUG << "DOWNRIGHT !!!!!!!!!";
			return (true);
		}
	}
	return (false);
}