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
   DEBUG << "INTERFACE READY\n";
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
    DEBUG << "check\n";
    for(std::map<std::string,bool>::const_iterator it=_screenStatus.begin() ; it!=_screenStatus.end() ; ++it)
    {
        if (it->first.compare(status) == 0)
        {
            DEBUG << "set to" << status << ", " << it->first << "\n";
            _screenStatus[it->first] = true;
        }
        else
            _screenStatus[it->first] = false;
    }
}

bool    Interface::checkScreenStatus(std::string status)
{
    DEBUG << "checkStatus\n";
    return ((this->_screenStatus.find(status))->second);
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

void    Interface::checkEvent(Player *currentPlayer) {
    
    (void)currentPlayer;
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
                        this->checkClickLeft(_event.mouseButton.x, _event.mouseButton.y);
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

/*
bool    Interface::onBoard(int x, int y)
{
    if (x <= BOARD_RIGHT + 20 && 
        x >= BOARD_LEFT - 20 &&
        y <= BOARD_UP - 20 &&
        y >= BOARD_DOWN  + 20)
        return true;
    else
        return false
}
*/

void    Interface::checkClickLeft(int x, int y)
{
    if (this->checkScreenStatus("inGame"))
    {
        if (true /*onBoard()*/)
            this->putStone(*(gomoku->getCurrentPlayer()->getSpriteStone()), x, y);
    }
    else
        DEBUG << "not in game\n";
}

void    Interface::update(void) {
        this->_window.clear();
        this->drawGame();
        this->_window.display();
}
