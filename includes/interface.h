#ifndef INTERFACE_H
# define INTERFACE_H

# include <SFML/Graphics.hpp>
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
		void	start(void);
		void	update(void);
		void	welcomeScreen(void);
		void	menuScreen(void);
		void	background(void);
		void	winEnd(void);
		void	timer(void);
		void	stone(sf::CircleShape, int, int);

	protected:
		Gomoku 				*gomoku;
		inline void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku;}
		
		sf::RenderWindow	_window;
		sf::Event			_event;
		sf::CircleShape		_stonePlayerOne;
		sf::CircleShape		_stonePlayerTwo;
};

#endif
