#include "assistedHumanPlayer.h"
#include "interface.h"
#include "rules.h"

AssistedHumanPlayer::AssistedHumanPlayer(std::array<unsigned char, 11> dw) : Player(), MinMaxDynamicPlayer(dw), HumanPlayer() {
    if (human) {
        DEBUG << "I'm human and robot, i'm the better of humanity\n";
    }else{
        DEBUG << "erreur constructeur, échec humanisation\n";}
}

AssistedHumanPlayer::~AssistedHumanPlayer() {
    DEBUG << "BYE ASSISTED HUMAN\n";
}

void AssistedHumanPlayer::playForHelp(Rules &rules, Interface &i) {
   DEBUG << "Need help? Wait...\n";
    int x = -1;
	int y = -1;
	startMinMax(x, y, rules);
	i.putStoneToHelp(x, y);
   DEBUG << "Try this, the best\n";
	return;
}

void AssistedHumanPlayer::play(Rules &rules, Interface &i) {
   DEBUG << "l'humain doit jouer :\n";
	HumanPlayer::play(rules,i);
   DEBUG << "merci d'avoir joue :\n";
}