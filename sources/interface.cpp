#include "interface.h"

using namespace sf;


Interface::Interface() : _window(VideoMode(WIDTH, HEIGHT), "GOMOKU"),
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

void    Interface::stone(CircleShape stone, int x, int y) {
        stone.setPosition(x, y);
        this->_window.draw(stone);
}

void    Interface::start(void) {
    while (this->_window.isOpen())
    {
        Event event;
        while (this->_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
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
