#include "gomoku.h"
#include "randomPlayer.h"
#include "defaultRules.h"


int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	srand(time(NULL));
	RandomPlayer p1;
	RandomPlayer p2;
	DefaultRules rules;
	Gomoku gomoku(p1, p2, rules);
	gomoku.start();
	success("end of the game");
	return (0);
}
