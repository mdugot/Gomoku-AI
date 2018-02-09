#include "interface.h"


Interface::Interface() : _window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU", Style::Titlebar | Style::Close)
{
   _window.setFramerateLimit(60);
   this->loadTexture();
   this->loadSprite();
   DEBUG << "I created\n";
}

//pour l'instant inutile à voir si à supprimer au final ... ?
void    Interface::start(void) {
  // _stonePlayerOne = gomoku->getWhitePlayer().getSpriteStone(); 
   //_stonePlayerTwo = gomoku->getBlackPlayer().getSpriteStone();
       //interface._stoneImg.createMaskFromColor(Color::White); // Masque de transparence;
   this->drawGame();
}

void    Interface::loadTexture(void) {
   if(!_stoneWhiteTexture.loadFromFile("./sprite/whiteStone.png")
    || !_stoneBlackTexture.loadFromFile("./sprite/blackStone.png")
    || !_backgroundTexture.loadFromFile("./sprite/background.png")
    || !_boardGameTexture.loadFromFile("./sprite/go.png")) {
       DEBUG << "Error during import " << std::endl;
   }
   else {
       _stoneWhiteTexture.setSmooth(true);
       _stoneBlackTexture.setSmooth(true);
       _backgroundTexture.setSmooth(true);
       _boardGameTexture.setSmooth(true);
   }
   DEBUG << "load\n";
}

void    Interface::loadSprite(void) {
    makeSprite(_backgroundSprite, _backgroundTexture, 1, 1, 0, 0);
    makeSprite(_boardGameSprite, _boardGameTexture, 1, 1, (_backgroundTexture.getSize().x - _boardGameTexture.getSize().x) / 2, (_backgroundTexture.getSize().y - _boardGameTexture.getSize().y) / 2);
    makeSprite(_whiteStone, _stoneWhiteTexture, 0.95f, 0.95f, 0, 0);
    makeSprite(_blackStone, _stoneBlackTexture, 0.95f, 0.95f, 0, 0);
    _whiteStone.setOrigin(25, 25);
    _blackStone.setOrigin(25, 25);
    _allSprite.pop_back();
    _allSprite.pop_back();
    //makeSprite(_backgroundSprite, _backgroundTexture, WIDTH / _backgroundTexture.getSize().x, HEIGHT / _backgroundTexture.getSize().y, 0, 0);
    //makeSprite(_boardGameSprite, _boardGameTexture, _backgroundSprite.getScale().x * 0.1f, _backgroundSprite.getScale().y * 0.1f, 50, 50);
   DEBUG << "loadS\n";
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
    while (_window.pollEvent(_event))
    {
        switch (_event.type)
        {
            case Event::Closed :
                _window.close();
                break;
            case Event::KeyPressed :
            {
                switch (_event.key.code)
                {
                    case Keyboard::Escape :
                       _window.close();
                        break;
                    case Keyboard::Q :
                        _window.close();
                        break;
                    default :
                        break;
                }
            }
            break;
            case Event::MouseMoved :
            {
                //clickX = _event.mouseMove.x;
                //clickY = _event.mouseMove.y;
            }
            break;
            case Event::MouseButtonPressed :
            {
                switch (_event.mouseButton.button)
                {
                    case Mouse::Left :
                    this->putStone(*(currentPlayer->getSpriteStone()), (int)_event.mouseButton.x, (int)_event.mouseButton.y);
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
        DEBUG << "draw\n";
        this->drawGame();
        DEBUG << "draw\n";
        this->_window.display();
}
