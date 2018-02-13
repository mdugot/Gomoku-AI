#ifndef PLAYER_H
#define PLAYER_H

#include "gomoku.h"
#include "utils.h"
#include "interface.h"

class Rules;

class Player
{
	friend class Gomoku;

	protected:

		unsigned int eatenStones;
		Gomoku *gomoku;
		Stone stoneColor;
		sf::Sprite	*stoneSprite;
		bool	human = false;
		
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline void setMyColor(Stone color) {this->stoneColor = color;}
		void putStone(int x, int y);
	
	public:

		Player();
		~Player();

		virtual void play(Rules &rules, Interface &i) = 0;
		inline Stone getColor() {return stoneColor;}
		inline sf::Sprite *getSpriteStone() {return stoneSprite;}
		inline void	setSpriteStone(sf::Sprite *stone) {this->stoneSprite = stone;}
};


#endif


