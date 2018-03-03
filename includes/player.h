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

		int nbCapture;
		Gomoku *gomoku;
		Player *enemy;
		Stone stoneColor;
		sf::Sprite	*stoneSprite;
		bool	played;
		sf::Vector2<int> coordPlayed; // MEMO : x et y ==> coordonnée du board dans Gomoku && w et z ==> coordonnés pour le board de l'interface.

		inline virtual void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline virtual void setColor(Stone color) {this->stoneColor = color;}
		void putStone(int x, int y);
		sf::Vector2<int> canteen[10];
	
	public:

		Player();
		~Player();

		virtual void play(Rules &rules, Interface &i )= 0;
		inline virtual void observe(Rules &rules, int x, int y, std::vector<std::pair<unsigned char, unsigned char>> &captured) {(void)rules; (void)x; (void)y; (void)captured;}
		inline virtual void observeMyCapture(std::vector<std::pair<unsigned char, unsigned char>> &captured) {(void)captured;}
		inline Stone getColor() {return stoneColor;}
		inline Player *getEnemy() {return enemy;}
		inline sf::Sprite *getSpriteStone() {return stoneSprite;}
		inline int getNbCapture() {return nbCapture;}
		inline sf::Vector2<int> getCoordPlayed(void) {return (coordPlayed);}
		inline sf::Vector2<int> getCoordCanteen(int index) {return (canteen[index]);}
		inline void	setEnemy(Player *en) {this->enemy = en;}
		inline void	setNbCapture(int nb) {this->nbCapture = nb;}
		inline void setCoordPlayed(int x, int y) {coordPlayed.x = x; coordPlayed.y = y;}
		inline void	setSpriteStone(sf::Sprite *stone) {this->stoneSprite = stone;}
		inline void	setPlayed(bool state) {played = state;}
		inline void	setCanteen(sf::Vector2<int> toCopy[10]) {int i = 0; while(i<10){canteen[i] = toCopy[i];i++;}}
};


#endif


