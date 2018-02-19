#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "gomoku.h"

class Interface;
class Rules;

class Player
{
	friend class Gomoku;

	protected:

		unsigned int eatenStones;
		Gomoku *gomoku;
		Stone stoneColor;
		sf::Sprite	*stoneSprite;
		bool	played;

		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline void setMyColor(Stone color) {this->stoneColor = color;}
		void putStone(int x, int y);
	
	public:

		Player();
		~Player();

		//virtual Vector2<int> play(Rules &rules, Vector2<int>) = 0;
		virtual void play(Rules &rules, Interface &i )= 0;
		inline Stone getColor() {return stoneColor;}
		inline sf::Sprite *getSpriteStone() {return stoneSprite;}
		inline void	setSpriteStone(sf::Sprite *stone) {this->stoneSprite = stone;}
		inline void	setPlayed(bool state) {played = state;}
};


#endif


