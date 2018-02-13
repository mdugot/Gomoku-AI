#include "utils.h"
#include "gomoku.h"
#include "randomPlayer.h"
#include "humanPlayer.h"
#include "defaultRules.h"
#include "interface.h"

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	srand(time(NULL));
	//RandomPlayer	p1;
	//RandomPlayer	p2;
	HumanPlayer		p1;
	HumanPlayer		p2;
	DefaultRules	rules;
	Interface		interface;
	Gomoku			gomoku(p1, p2, rules, interface);
	gomoku.start();
	success("end of the game");
	return (0);
}
