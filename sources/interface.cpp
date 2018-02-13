#include "interface.h"


Interface::Interface() : _window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU", Style::Titlebar | Style::Close)
{
   _window.setFramerateLimit(60);
   this->loadTexture();
   this->loadSprite();
   _screenStatus["inGame"] = false;
   _screenStatus["inMenu"] = false;
   _screenStatus["inEndScreen"] = false;
   _screenStatus["inWelcomeScreen"] = true;
   initCoordBoard();
   DEBUG << "INTERFACE READY\n";
}

void    Interface::initCoordBoard(void) {
    int i = 0;
    int j = 0;
    float step = 49.445f;//(float)((BOARD_RIGHT - BOARD_LEFT) / 18);
    DEBUG << "step:" << step;
    float stepy = 0;
    float stepx = 0;
    int y = BOARD_UP;
    while (i < GW) {
        int x = BOARD_LEFT;
        j = 0;
        stepx = 0;
        while (j < GH) {
            coordBoard[i][j] = Vector2<int>((int)(x + stepx), (int)(y + stepy));
            stepx+= step;
            j++;
        }
        stepy += step;
        i++;
    }
}

void    Interface::printCoordBoard(void) {
    int i = 0;
    int j = 0;
    while (i < GW) {
        j = 0;
        while (j < GH) {
            DEBUG << coordBoard[i][j].x << "," << coordBoard[i][j].y << "|";
            this->putStone(*(gomoku->getCurrentPlayer()->getSpriteStone()), coordBoard[i][j].x, coordBoard[i][j].y);
            j++;
        }
        DEBUG << "\n";
        i++;
    }
}

void    Interface::setStoneOnClick(Player &current, int clickx, int clicky) {
    int i = 0;
    int j = 0;
    while (i < GW) {
        j = 0;
        while (j < GH) {
            if (clickx <= coordBoard[i][j].x + 8 && clickx >= coordBoard[i][j].x - 8 &&
                clicky <= coordBoard[i][j].y + 8 && clicky >= coordBoard[i][j].y - 8) {
                //AJOUTER AUSSI LES AUTRES REGLES A CHECKER
                //if (gomoku->getStone(i, j) == FREE) {
                if (gomoku->rules.canPutstone(current, i, j)) {
                    //this->putStone(*(gomoku->getCurrentPlayer()->getSpriteStone()), coordBoard[i][j].x, coordBoard[i][j].y);
                    //gomoku->setStone(gomoku->getCurrentPlayer()->getColor(), i, j);
                    this->putStone(*(current->getSpriteStone()), coordBoard[i][j].x, coordBoard[i][j].y);
                    gomoku->setStone(current->getColor(), i, j);
                    current->setPlayed(true);
                    return; 
                }
            }
            j++;
        }
        i++;
    }
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
}

void    Interface::loadSprite(void) {
    makeSprite(_backgroundSprite, _backgroundTexture, 1, 1, 0, 0);
    makeSprite(_boardGameSprite, _boardGameTexture, 1, 1, (_backgroundTexture.getSize().x - _boardGameTexture.getSize().x) / 2, (_backgroundTexture.getSize().y - _boardGameTexture.getSize().y) / 2);
    makeSprite(_whiteStone, _stoneWhiteTexture, 0.95f, 0.95f, 0, 0);
    makeSprite(_blackStone, _stoneBlackTexture, 0.95f, 0.95f, 0, 0);
    _whiteStone.setOrigin(_stoneWhiteTexture.getSize().x / _whiteStone.getScale().x / 2, _stoneWhiteTexture.getSize().y / _whiteStone.getScale().y / 2);
    _blackStone.setOrigin(_stoneBlackTexture.getSize().x / _blackStone.getScale().x / 2, _stoneBlackTexture.getSize().y / _blackStone.getScale().y / 2);
    _allSprite.pop_back();
    _allSprite.pop_back();
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

void    Interface::setScreenStatus(std::string status)
{
    for(std::map<std::string,bool>::const_iterator it=_screenStatus.begin() ; it!=_screenStatus.end() ; ++it) {
            _screenStatus[it->first] = false;
    }
    _screenStatus[status] = true;
}

bool    Interface::checkScreenStatus(std::string status)
{
    return (this->_screenStatus[status]);
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

void    Interface::endScreen(void) {
    //draw endScreen
    this->setScreenStatus("inEnd");
}

void    Interface::menuScreen(void) {
    //drawMenu
    this->setScreenStatus("inMenu");
}

void    Interface::background(void) {

}

void    Interface::timer(void) {

}

void    Interface::putStone(Sprite stone, int x, int y) {
        stone.setPosition(x, y);
        _allSprite.push_back(stone);
}

void    Interface::checkEvent(Player &current) {
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
                        this->checkClickLeft(current, _event.mouseButton.x, _event.mouseButton.y);
                        DEBUG << "xy(" <<_event.mouseButton.x << "," << _event.mouseButton.y << ")\n"; 
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


bool    Interface::onBoard(int x, int y)
{
    if (x <= BOARD_RIGHT + MARGE && 
        x >= BOARD_LEFT - MARGE &&
        y >= BOARD_UP - MARGE &&
        y <= BOARD_DOWN  + MARGE)
        return true;
    else
        return false;
}


void    Interface::checkClickLeft(Player &current, int x, int y)
{
    if (this->checkScreenStatus("inGame"))
    {
        if (!current->human && onBoard(x, y))
            this->setStoneOnClick(current, x, y); //this->putStone(*(gomoku->getCurrentPlayer()->getSpriteStone()), x, y);
        else
            DEBUG << "out of board add other feature interaction\n";
    }
    else
        DEBUG << "not in game add feature menu and other\n";
}

void    Interface::update(void) {
        this->_window.clear();
        this->drawGame();
        this->_window.display();
}
