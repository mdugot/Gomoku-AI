#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "utils.h"

class HumanPlayer : public Player
{
	private:
		bool human = true;
		bool played;

	
	public:

		HumanPlayer();
		~HumanPlayer();

		virtual void play(Rules &rules, Interface &i);
		inline void	setPlayed(bool state) {played = state;}
};


#endif

