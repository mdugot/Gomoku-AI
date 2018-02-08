#include "interface.h"


Interface::Interface() : _window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU")
{
   _window.setFramerateLimit(60);
   this->loadTexture();
   this->loadSprite();
}

//pour l'instant inutile à voir si à supprimer au final ... ?
void    Interface::start(void) {
   _stonePlayerOne = gomoku->getWhitePlayer().getSpriteStone(); 
   _stonePlayerTwo = gomoku->getBlackPlayer().getSpriteStone();
   this->drawGame();
}

void    Interface::loadTexture(void) {
   if(!_stoneTexture.loadFromFile("./sprite/stone.png")
    || !_backgroundTexture.loadFromFile("./sprite/boisFonce.jpeg")
    || !_boardGameTexture.loadFromFile("./sprite/boisClair.png")
    || !_gridTexture.loadFromFile("./sprite/grid.png")) {
       DEBUG << "Error during import " << std::endl;
   }
   else {
       _stoneTexture.setSmooth(true);
       _backgroundTexture.setSmooth(true);
       _boardGameTexture.setSmooth(true);
       _gridTexture.setSmooth(true);
       _gridTexture.setRepeated(true);
   }
}

void    Interface::loadSprite(void) {
    makeSprite(_backgroundSprite, _backgroundTexture, WIDTH / _backgroundTexture.getSize().x, HEIGHT / _backgroundTexture.getSize().y, 0, 0);
    makeSprite(_boardGameSprite, _boardGameTexture, _backgroundSprite.getScale().x * 0.1f, _backgroundSprite.getScale().y * 0.1f, 50, 50);
    makeSprite(_gridSprite, _gridTexture, _boardGameSprite.getScale().x, _boardGameSprite.getScale().y, _boardGameSprite.getPosition().x, _boardGameSprite.getPosition().y);
}

void    Interface::makeSprite(Sprite &sprite, Texture &texture, float sizeX, float sizeY, int posX, int posY) {
    sprite.setTexture(texture);
    sprite.setScale(sizeX, sizeY);
    sprite.setPosition(posX, posY);
    _allSprite.push_back(sprite);
}

Interface::~Interface() {

}

void    Interface::drawWindow(void) {
    
}

void    Interface::drawGame(void) {
    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        this->_window.draw(*it);
    }
}

void    Interface::welcomeScreen(void) {

}

void    Interface::menuScreen(void) {

}

void    Interface::background(void) {

}

void    Interface::timer(void) {

}

void    Interface::putStone(Sprite stone, int x, int y) {
        stone.setPosition(x, y);
        _allSprite.push_back(stone);
}

/*
///////// MERLIN ///////////
// Je n'arrive pas à faire ne sorte de récupérer la pierre associé au currentPlayer à partir de ma classe interface, tu paux m'aider ? ///
//////////////////////////////////////////////////
CircleShape Interface::getCurrentStonePlayer(void)
{
        Player *test = gomoku->getCurrentPlayer();
        CircleShape *tmp = test->getStoneSprite();
        return (tmp);
        //return (gomoku->getCurrentPlayer).getStoneSprite();
        
        return (_stonePlayerOne);
}*/


void    Interface::checkEvent(Player *currentPlayer) {
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
                    this->putStone(currentPlayer->getSpriteStone(), (int)_event.mouseButton.x, (int)_event.mouseButton.y);
                    DEBUG << "put\n";
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
