#include "interface.h"


Interface::Interface(Gomoku &gomoku) : _gomoku(gomoku),
_window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU"),
_stonePlayerOne(10.0f), _stonePlayerTwo(10.0f)
{
    _stonePlayerOne.setFillColor(sf::Color::Yellow);
    _stonePlayerTwo.setFillColor(sf::Color::Green);

}

Interface::~Interface() {

}

void    Interface::drawWindow(void) {
    
}

void    Interface::drawGame(void) {
    this->background();
    this->stone(_stonePlayerOne, 10, 10);
    this->stone(_stonePlayerTwo, 30, 30);
    this->stone(_stonePlayerTwo, 50, 50);
}

void    Interface::welcomeScreen(void) {

}

void    Interface::menuScreen(void) {

}

void    Interface::background(void) {

}

void    Interface::timer(void) {

}

void    Interface::stone(sf::CircleShape stone, int x, int y) {
        stone.setPosition(x, y);
        this->_window.draw(stone);
}

void    Interface::start(void) {
    while (this->_window.isOpen())
    {
        sf::Event event;
        while (this->_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->_window.close();
        }
        this->update();
    }
}

void    Interface::update(void) {
        //this->_window.clear();
        this->drawGame();
        this->_window.display();
}
