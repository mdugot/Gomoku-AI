#ifndef INTERFACE_H
# define INTERFACE_H

# include "utils.h"
# include "gomoku.h"

# define WIDTH	1200 // a essayer
# define HEIGHT	1200

using namespace sf;

class Interface {

	friend class Gomoku;

	public:
		Interface();
		~Interface();

		void	drawWindow(void);
		void	drawGame(void);
		void	update(void);
		void	welcomeScreen(void);
		void	menuScreen(void);
		void	background(void);
		void	winEnd(void);
		void	timer(void);
		void	putStone(sf::CircleShape, int, int);
		sf::CircleShape	getCurrentStonePlayer(void);

	protected:
		Gomoku 				*gomoku;
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		inline sf::RenderWindow &getWindow(void) {return this->_window;}
		inline sf::Event &getEvent(void) {return this->_event;}
		
		sf::RenderWindow	_window;
		sf::Event			_event;
		sf::CircleShape		_stonePlayerOne;
		sf::CircleShape		_stonePlayerTwo;

		void	checkEvent(void);
		void	checkInput(void);
		int	clickX;
		int clickY;
};

#endif
