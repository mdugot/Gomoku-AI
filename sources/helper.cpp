#include "helper.h"
#include "interface.h"
#include "rules.h"

Helper::Helper(std::array<unsigned char, 11> dw) : MinMaxDynamicPlayer(dw) {
    DEBUG << "HELLO HELPER";
}

Helper::~Helper() {
    DEBUG << "BYE HELPER";
}

void Helper::play(Rules &rules, Interface &i) {
	int x = -1;
	int y = -1;
    DEBUG << "HELPER 1 : ";
	//startMinMax(x, y, rules);
    DEBUG << "HELPER 2 : ";
	i.putStoneToHelp(3, 3);
    DEBUG << "HELPER ADVICE : ";
}