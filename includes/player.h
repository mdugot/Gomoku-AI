#ifndef PLAYER_H
#define PLAYER_H

#include "gomoku.h"
#include "utils.h"

class Rules;

class Player
{
	friend class Gomoku;

	protected:

		unsigned int eatenStones;
		Gomoku *gomoku;
		Player *ennemy;
		Stone stoneColor;
		sf::CircleShape	spriteStone;
		
		inline virtual void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline void setEnnemy(Player *e) {this->ennemy = e;}
		inline virtual void setColor(Stone color) {this->stoneColor = color;}
		inline void setSpriteStone(sf::Color color) {spriteStone.setRadius(10.0f);spriteStone.setFillColor(color); }
		void putStone(int x, int y);
	
	public:

		Player();
		~Player();

		virtual void play(Rules &rules, int &x, int &y) = 0;
		inline virtual void observe(Rules &rules, int x, int y) {(void)rules; (void)x; (void)y;}
		inline Stone getColor() {return stoneColor;}
		inline sf::CircleShape getSpriteStone() {return spriteStone;}
};


#endif


