#include "gomoku.h"
#include "randomPlayer.h"
#include "defaultRules.h"
#include "interface.h"

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	srand(time(NULL));
	RandomPlayer p1;
	RandomPlayer p2;
	DefaultRules rules;
	Gomoku gomoku(p1, p2, rules);
	Interface interface(gomoku);
	interface.start();
	gomoku.start();
	success("end of the game");
	return (0);
}
