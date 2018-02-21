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
		Stone stoneColor;
		sf::Sprite	*stoneSprite;
		bool	played;
		sf::Vector2<int> coordPlayed; // MEMO : x et y ==> coordonnée du board dans Gomoku && w et z ==> coordonnés pour le board de l'interface.

		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline void setMyColor(Stone color) {this->stoneColor = color;}
		void putStone(int x, int y);
	
	public:

		Player();
		~Player();

		virtual void play(Rules &rules, Interface &i )= 0;
		inline Stone getColor() {return stoneColor;}
		inline sf::Sprite *getSpriteStone() {return stoneSprite;}
		inline int getNbCapture() {return nbCapture;}
		inline sf::Vector2<int> getCoordPlayed(void) {return (coordPlayed);}
		inline void	setNbCapture(int nb) {this-> nbCapture = nb;}
		inline void setCoordPlayed(int x, int y) {coordPlayed.x = x; coordPlayed.y = y;}
		inline void	setSpriteStone(sf::Sprite *stone) {this->stoneSprite = stone;}
		inline void	setPlayed(bool state) {played = state;}
};


#endif


