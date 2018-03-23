#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "gomoku.h"
#include "heuristicBoard.h"

class Interface;
class Rules;

class Player
{
	friend class Gomoku;

	protected:

		HeuristicBoard myHeuristic;
		HeuristicBoard ennemyHeuristic;

		int nbCapture;
		Gomoku *gomoku;
		Player *enemy;
		Stone stoneColor;
		sf::Sprite	*stoneSprite;
		bool	played;
		sf::Vector2<int> coordPlayed; // MEMO : x et y ==> coordonnée du board dans Gomoku

		inline virtual void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku; myHeuristic.gomoku = gomoku; ennemyHeuristic.gomoku = gomoku;}
		inline virtual void setColor(Stone color) {this->stoneColor = color; myHeuristic.stone =color; ennemyHeuristic.stone = (color == WHITE ? BLACK : WHITE);}
		void putStone(int x, int y);
		sf::Vector2<int> canteen[10];
	
	public:

		Player();
		virtual ~Player();

		virtual void play(Rules &rules, Interface &i )= 0;
		virtual void observe(Rules &rules, int x, int y, std::vector<std::pair<unsigned char, unsigned char>> &captured);
		virtual void observeMyCapture(std::vector<std::pair<unsigned char, unsigned char>> &captured);
		inline Stone getColor() {return stoneColor;}
		inline HeuristicBoard *getMyHeuristic() {return &myHeuristic;}
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


