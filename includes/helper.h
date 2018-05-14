#ifndef HELPER_H
# define HELPER_H

#include "player.h"
#include "minMaxDynamicPlayer.h"

class Helper : public MinMaxDynamicPlayer
{
    public:
    
    Helper(std::array<unsigned char, 11> dw);
    ~Helper();

    virtual void play(Rules &rules, Interface &i);

};

# endif