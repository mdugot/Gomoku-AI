#include "utils.h"
#include "gomoku.h"
#include "heuristicBoard.h"
#include "randomPlayer.h"
#include "minMaxPlayer.h"
#include "minMaxDynamicPlayer.h"
#include "defaultRules.h"
#include "interface.h"

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	srand(time(NULL));
//	srand(7);
	MinMaxDynamicPlayer		white(4);
	MinMaxDynamicPlayer		black(6);
	DefaultRules			rules;
	Interface				interface;
	Gomoku					gomoku(white, black, rules, interface);
	gomoku.start();

	success("end of the game");
	return (0);
}
