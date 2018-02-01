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
	while (!rules.checkEnd()) {
		currentPlayer->play(rules);
		if (currentPlayer == &blackPlayer)
			currentPlayer = &whitePlayer;
		else
			currentPlayer = &blackPlayer;
		rules.turnCounter += 1;
	}
}
