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
# define YES_LEFT	150
# define YES_RIGHT	500
# define YES_UP	450
# define YES_DOWN	555
# define NO_LEFT	650
# define NO_RIGHT	995
# define NO_UP	450
# define NO_DOWN	555
# define BLACKCANTEENX 240
# define BLACKCANTEENY 40
# define WHITECANTEENX 960
# define WHITECANTEENY 860
# define CENTER_MAX_DISTANCE 20

typedef enum State {
	WELCOME = 1, MENU = 2, GAME = 3, WHITEWIN = 4, BLACKWIN = 5, EQUAL = 6, AGAIN = 7, PAUSE = 8, GOODBYE = 0
} State;

class Interface {

	friend class Gomoku;
	friend class Menu;

	public:
		Interface();
		~Interface();

		void	drawGame(void);
		void	update(void);
		void	putStone(sf::Sprite, int, int);
		void	printCoordBoard(void);
		void	makeSprite(sf::Sprite &s, sf::Texture &t, float sy, float sx, int px, int py);
		void	cleanInterface(void);
		void	cleanSpriteList(void);
		void	cleanTextList(void);
		void	checkClickLeft(Player *current, int x, int y);
		void	setStoneOnClick(Player &player, int x, int y);
		void	checkEvent(Player *current);
		void	checkEventAgain();
		
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
		sf::Vector2<int>	turnCoordInterfaceInGomokuBoardIndex(int screenX, int screenY);
		
		sf::Sprite			_whiteStone;
		sf::Sprite			_blackStone;
		
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		//std::map<std::string, bool> _screenStatus;

	private:
		void	welcomeScreen(void);
		void	menuScreen(void);
		void	whiteWinScreen(void);
		void	blackWinScreen(void);
		void	equalScreen(void);
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
		void	putPreviewStone(Player &current, int mouseX, int mouseY);
		void	unputPreviewStone(int mouseX, int mouseY);
		void	removeStone(int i, int j);
		bool	onBoard(int x, int y);
		bool	onAgainYes(int x, int y);
		bool	onAgainNo(int x, int y);

		//to previzualize stone
		bool				previewStone;
		sf::Vector2<int>	coordPreviewStone;
		sf::Sprite			previewStoneFree;
		sf::Sprite			previewStoneForbidden;

		sf::Sprite			_backgroundSprite;
		sf::Sprite			_boardGameSprite;
		sf::Sprite			_goodByeSprite;
		sf::Sprite			_helloSprite;
		sf::Sprite			_againSprite;
		sf::Sprite			_blackWinSprite;
		sf::Sprite			_whiteWinSprite;
		sf::Sprite			_equalitySprite;
		sf::Sprite			_boxSprite;
		sf::Sprite			_boxSelectSprite;
		sf::Sprite			_againYesSprite;
		sf::Sprite			_againNoSprite;

		sf::Texture			_stoneWhiteTexture;
		sf::Texture			_stoneBlackTexture;
		sf::Texture			_backgroundTexture;
		sf::Texture			_boardGameTexture;
		sf::Texture			_goodByeTexture;
		sf::Texture			_helloTexture;
		sf::Texture			_againTexture;
		sf::Texture			_whiteWinTexture;
		sf::Texture			_blackWinTexture;
		sf::Texture			_equalityTexture;
		sf::Texture			_againYesTexture;
		sf::Texture			_againNoTexture;
		sf::Texture			_boxTexture;
};

#endif
