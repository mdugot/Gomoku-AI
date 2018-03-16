#ifndef INTERFACE_H
#define INTERFACE_H

#include "gomoku.h"
#include "player.h"
#include "menu.h"

# define WIDTH	1200
# define HEIGHT	900
# define BOARD_LEFT	240
# define BOARD_RIGHT	960
# define BOARD_UP	90
# define BOARD_DOWN	810
# define MARGE	10
# define BLACKCANTEENX 240
# define BLACKCANTEENY 40
# define WHITECANTEENX 960
# define WHITECANTEENY 860

typedef enum State {
	WELCOME = 1, MENU = 2, GAME = 3, SCORE = 4, AGAIN = 5, PAUSE = 6, GOODBYE = 0
} State;

class Interface {

	friend class Gomoku;
	friend class Menu;

	public:
		Interface(/*Menu &menu*/);
		~Interface();

		void	drawGame(void);
		void	update(void);
		void	putStone(sf::Sprite, int, int);
		void	printCoordBoard(void);
		void	makeSprite(sf::Sprite &s, sf::Texture &t, float sy, float sx, int px, int py);
		void	cleanSpriteList(void);
		void	cleanTextList(void);
		void	checkClickLeft(Player &current, int x, int y);
		bool	onBoard(int x, int y);
		void	setStoneOnClick(Player &player, int x, int y);
		void	checkEvent(Player &current);
		
		void	setState(State newState);
		void	capture(Player &current, sf::Sprite *spriteEnemy, int x, int y);

		inline	State				&getState(void) {return (state);}
		inline	sf::RenderWindow	&getWindow(void) {return this->_window;}
		inline	sf::Event			&getEvent(void) {return this->_event;}
		inline	sf::Vector2<int>		&getCoordBoard(int x, int y){return (coordBoard[x][y]);}	
		sf::Vector2<int> whiteCanteen[10];
		sf::Vector2<int> blackCanteen[10];

	protected:
		Menu				menu;
		Gomoku 				*gomoku;
		
		State				state;
		sf::RenderWindow	_window;
		sf::Event			_event;
		std::list<sf::Sprite>			_allSprite;
		std::list<sf::Text*>			_allText;
		sf::Vector2<int>	coordBoard[GW][GH];
		
		sf::Sprite			_whiteStone;
		sf::Sprite			_blackStone;
		
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		//std::map<std::string, bool> _screenStatus;

	private:
		void	welcomeScreen(void);
		void	menuScreen(void);
		void	scoreScreen(void);
		void	againScreen(void);
		void	gameScreen(void);
		void	goodByeScreen(void);
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
		sf::Sprite			_goodByeSprite;
		sf::Sprite			_helloSprite;

		sf::Texture			_stoneWhiteTexture;
		sf::Texture			_stoneBlackTexture;
		sf::Texture			_backgroundTexture;
		sf::Texture			_boardGameTexture;
		sf::Texture			_goodByeTexture;
		sf::Texture			_helloTexture;

};

#endif
