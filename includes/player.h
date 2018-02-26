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

		unsigned int nbCapture;
		Gomoku *gomoku;
		Player *enemy;
		Stone stoneColor;
		sf::Sprite	*stoneSprite;
		bool	played;
		sf::Vector2<int> coordPlayed; // MEMO : x et y ==> coordonnée du board dans Gomoku && w et z ==> coordonnés pour le board de l'interface.
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline void setMyColor(Stone color) {this->stoneColor = color;}
		void putStone(int x, int y);
		sf::Vector2<int> canteen[10];
	
	public:

		Player();
		~Player();

		virtual void play(Rules &rules, Interface &i )= 0;
		inline Stone getColor() {return this->stoneColor;}
		inline sf::Sprite *getSpriteStone() {return this->stoneSprite;}
		inline int getNbCapture() {return this->nbCapture;}
		inline sf::Vector2<int> getCoordPlayed(void) {return (this->coordPlayed);}
		inline Player *getEnemy(void) {return (this->enemy);}
		inline void	setNbCapture(int nb) {this-> nbCapture = nb;}
		inline void setCoordPlayed(int x, int y) {this->coordPlayed.x = x; this->coordPlayed.y = y;}
		inline void	setSpriteStone(sf::Sprite *stone) {this->stoneSprite = stone;}
		inline void	setPlayed(bool state) {this->played = state;}
		inline void	setEnemy(Player *en) {this->enemy = en;}
		inline void	setCanteen(sf::Vector2<int> toCopy[10]) {int i = 0; while (i < 10) {this->canteen[i] = toCopy[i];i++;}}
};


#endif


