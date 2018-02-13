#ifndef INTERFACE_H
# define INTERFACE_H

# include "utils.h"
# include "gomoku.h"
# include "player.h"
# include "humanPlayer.h"

# define WIDTH	1600
# define HEIGHT	1200
# define BOARD_LEFT	355
# define BOARD_RIGHT	1245
# define BOARD_UP	155
# define BOARD_DOWN	1045
# define MARGE	10

using namespace sf;

class Interface {

	friend class Gomoku;

	public:
		Interface();
		~Interface();

		void	start(void);
		void	drawWindow(void);
		void	drawGame(void);
		void	update(void);
		void	endScreen(void);
		void	welcomeScreen(void);
		void	menuScreen(void);
		void	background(void);
		void	winEnd(void);
		void	timer(void);
		void	putStone(sf::Sprite, int, int);
//		sf::CircleShape	getCurrentStonePlayer(void);
		inline sf::RenderWindow &getWindow(void) {return this->_window;}
		inline sf::Event &getEvent(void) {return this->_event;}
		void	loadTexture(void);
		void	loadSprite(void);
		void	initCoordBoard(void);
		void	printCoordBoard(void);
		void	makeSprite(sf::Sprite &s, sf::Texture &t, float sy, float sx, int px, int py);
		void	checkClickLeft(Player &current, int x, int y);
		bool	checkScreenStatus(std::string toCheck);
		void	setScreenStatus(std::string status);
		bool	onBoard(int x, int y);
		void	setStoneOnClick(Player &player, int x, int y);
		void	checkEvent(Player &current);

	protected:
		Gomoku 				*gomoku;
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		
		sf::RenderWindow	_window;
		sf::Event			_event;
		sf::Sprite			_whiteStone;
		sf::Sprite			_blackStone;
		sf::Sprite			_backgroundSprite;
       	sf::Sprite			_boardGameSprite;
		sf::Texture			_stoneWhiteTexture;
		sf::Texture			_stoneBlackTexture;
		sf::Texture			_backgroundTexture;
       	sf::Texture			_boardGameTexture;
		std::list<sf::Sprite>			_allSprite;

		int	clickX;
		int clickY;
		std::map<std::string, bool> _screenStatus;
		Vector2<int>	coordBoard[GW][GH];

};

#endif
