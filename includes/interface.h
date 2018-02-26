#ifndef INTERFACE_H
#define INTERFACE_H

#include "gomoku.h"
#include "player.h"

# define WIDTH	1600
# define HEIGHT	1200
# define BOARD_LEFT	355
# define BOARD_RIGHT	1245
# define BOARD_UP	155
# define BOARD_DOWN	1045
# define MARGE	10
# define BLACKCANTEENX 355
# define BLACKCANTEENY 100
# define WHITECANTEENX 1245
# define WHITECANTEENY 1100

typedef enum State {
	WELCOME = 1, MENU = 2, GAME = 3, SCORE = 4, AGAIN = 5, PAUSE = 6, GOODBYE = 0
} State;

class Interface {

	friend class Gomoku;

	public:
		Interface();
		~Interface();

		void	drawGame(void);
		void	update(void);
		void	putStone(sf::Sprite, int, int);
		void	printCoordBoard(void);
		void	makeSprite(sf::Sprite &s, sf::Texture &t, float sy, float sx, int px, int py);
		void	cleanSpriteList(void);
		void	checkClickLeft(Player &current, int x, int y);
		bool	onBoard(int x, int y);
		void	setStoneOnClick(Player &player, int x, int y);
		void	checkEvent(Player &current);
		
		void	setState(State newState);
		void	capture(Player &current, sf::Sprite *spriteEnemy, int x, int y, int x2, int y2);

		inline	State				&getState(void) {return (state);}
		inline	sf::RenderWindow	&getWindow(void) {return this->_window;}
		inline	sf::Event			&getEvent(void) {return this->_event;}
		inline	sf::Vector2<int>		&getCoordBoard(int x, int y){return (coordBoard[x][y]);}	
		sf::Vector2<int> whiteCanteen[10];
		sf::Vector2<int> blackCanteen[10];

	protected:
		Gomoku 				*gomoku;
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		
		State				state;
		sf::RenderWindow	_window;
		sf::Event			_event;
		std::list<sf::Sprite>			_allSprite;
		//std::map<std::string, bool> _screenStatus;
		sf::Vector2<int>	coordBoard[GW][GH];
		
		sf::Sprite			_whiteStone;
		sf::Sprite			_blackStone;

	private:
		void	welcomeScreen(void);
		void	menuScreen(void);
		void	scoreScreen(void);
		void	againScreen(void);
		void	gameScreen(void);
		void	endScreen(void);
		void	startPauseScreen(void);
		void	stopPauseScreen(void);
		void	captureZone(void);
		void	timer(void);
		void	loadTexture(void);
		void	loadSprite(void);
		void	initCoordBoard(void);
		void	initCoordCanteen(void);
		
		sf::Sprite			_backgroundSprite;
		sf::Sprite			_boardGameSprite;

		sf::Texture			_stoneWhiteTexture;
		sf::Texture			_stoneBlackTexture;
		sf::Texture			_backgroundTexture;
		sf::Texture			_boardGameTexture;

};

#endif
