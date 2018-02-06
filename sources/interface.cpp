#include "interface.h"


Interface::Interface() : _window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU")
{
   _stonePlayerOne.setRadius(10.0f); 
   _stonePlayerOne.setFillColor(Color::White); 
   _stonePlayerTwo.setRadius(10.0f); 
   _stonePlayerTwo.setFillColor(Color::Black); 
}

Interface::~Interface() {

}

void    Interface::drawWindow(void) {
    
}

void    Interface::drawGame(void) {
    this->background();
    this->putStone(_stonePlayerOne, 10, 10);
    this->putStone(_stonePlayerTwo, 30, 30);
    this->putStone(_stonePlayerTwo, 50, 50);
}

void    Interface::welcomeScreen(void) {

}

void    Interface::menuScreen(void) {

}

void    Interface::background(void) {

}

void    Interface::timer(void) {

}

void    Interface::putStone(CircleShape stone, int x, int y) {
        stone.setPosition(x, y);
        this->_window.draw(stone);
}


///////// MERLIN ///////////
// Je n'arrive pas à faire ne sorte de récupérer la pierre associé au currentPlayer à partir de ma classe interface, tu paux m'aider ? ///
//////////////////////////////////////////////////
CircleShape Interface::getCurrentStonePlayer(void)
{
        /*Player *test = gomoku->getCurrentPlayer();
        CircleShape *tmp = test->getStoneSprite();
        return (tmp);
        //return (gomoku->getCurrentPlayer).getStoneSprite();
        */
        return (_stonePlayerOne);
}


void    Interface::checkEvent(void) {
    while (_window.pollEvent(_event)) // Boucle des évènements en attente
    {
        switch (_event.type) // Type de l'évènement
        {
            case Event::Closed : // Bouton de fermeture
                _window.close();
                break;
            case Event::KeyPressed : // Appui sur une touche du clavier
            {
                switch (_event.key.code) // La touche qui a été appuyée
                {
                    case Keyboard::Escape :
                       _window.close();
                        break;
                    case Keyboard::Q : // Echap
                        _window.close();
                        break;
                    default :
                        break;
                }
            }
            break;
            case Event::MouseMoved : // Mouvement de la souris
            {
                clickX = _event.mouseMove.x;
                clickY = _event.mouseMove.y;
            }
            break;
            case Event::MouseButtonPressed :
            {
                switch (_event.mouseButton.button)
                {
                    case Mouse::Left :
                    this->putStone(getCurrentStonePlayer(), (int)_event.mouseButton.x, (int)_event.mouseButton.y);
                    break;
                default :
                    break;
                }
            }
            break;
            default :
                break;
        }
    }
}

void    Interface::update(void) {
        //this->_window.clear();
        this->drawGame();
        this->_window.display();
}
