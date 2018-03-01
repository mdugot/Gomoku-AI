#include "interface.h"
#include "gomoku.h"
#include "player.h"
#include "rules.h"
#include "utils.h"

using namespace sf;
//TO-DO : fonction pour nettoyer (free) et réinitiliaser la liste de sprite du jeu à afficher.

Interface::Interface() : _window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU", Style::Titlebar | Style::Close)
{
   _window.setFramerateLimit(60);
   _window.setVerticalSyncEnabled(true);
   this->loadTexture();
   this->loadSprite();
   initCoordBoard();
   initCoordCanteen();
   this->setState(WELCOME);
   DEBUG << "INTERFACE READY\n";
}

void    Interface::initCoordBoard(void) {
    int i = 0;
    int j = 0;
    float step = 49.445f;//(float)((BOARD_RIGHT - BOARD_LEFT) / 18);
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

void    Interface::initCoordCanteen(void) {
    int i = 0;
    float step = 49.445f;//(float)((BOARD_RIGHT - BOARD_LEFT) / 18);
    float stepx = 0;
    int y = BLACKCANTEENY;
    int x = BLACKCANTEENX;
    stepx = 0;
    while (i < NB_CAPTURE_TO_WIN) {
        blackCanteen[i] = Vector2<int>((int)(x + stepx), (int)(y));
            //this->putStone(this->_blackStone, blackCanteen[i].x, blackCanteen[i].y);
            stepx+= step;
        i++;
    }
    i = 0;
    stepx = 0;
    y = WHITECANTEENY;
    x = WHITECANTEENX;
    stepx = 0;
    while (i < NB_CAPTURE_TO_WIN) {
        whiteCanteen[i] = Vector2<int>((int)(x - stepx), (int)(y));
       // this->putStone(this->_whiteStone, whiteCanteen[i].x, whiteCanteen[i].y);
        stepx+= step;
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
//            this->putStone(*(gomoku->getCurrentPlayer()->getSpriteStone()), coordBoard[i][j].x, coordBoard[i][j].y);
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
                if (gomoku->getRules().canPutStone(current, i, j)) {
                    current.setCoordPlayed(i, j);
                    current.setPlayed(true);
                }
                return; 
                }
            j++;
            }
        i++;
    }
}


void	Interface::capture(Player &current, sf::Sprite *spriteEnemy, int x1, int y1, int x2, int y2) {
    (void)current;
    (void)spriteEnemy;
    int i = getCoordBoard(x1,y1).x;
    int j = getCoordBoard(x1,y1).y;
    int i2 = getCoordBoard(x2,y2).x;
    int j2 = getCoordBoard(x2,y2).y;
    Vector2<int> pos;
    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        pos = (Vector2<int>)(*it).getPosition();
        if ((pos.x == i && pos.y == j) || (pos.x == i2 && pos.y == j2)){
            it = _allSprite.erase(it);
            DEBUG << "REMOVE\n";
        }
    }
    this->putStone(*spriteEnemy, current.getCoordCanteen(current.getNbCapture() - 2).x, current.getCoordCanteen(current.getNbCapture() - 2).y);
    this->putStone(*spriteEnemy, current.getCoordCanteen(current.getNbCapture() - 1).x, current.getCoordCanteen(current.getNbCapture() - 1).y);
}

//TO-DO : Ajout texture des autres States ici.
void    Interface::loadTexture(void) {
   if(!_stoneWhiteTexture.loadFromFile("./sprite/whiteStone.png")
    || !_stoneBlackTexture.loadFromFile("./sprite/blackStone.png")
    || !_backgroundTexture.loadFromFile("./sprite/background.png")
    || !_boardGameTexture.loadFromFile("./sprite/go.png")
    || !_goodByeTexture.loadFromFile("./sprite/goodBye.png")) {
       DEBUG << "Error during import " << std::endl;
       exit(1);
   }
   else {
       _stoneWhiteTexture.setSmooth(true);
       _stoneBlackTexture.setSmooth(true);
       _backgroundTexture.setSmooth(true);
       _boardGameTexture.setSmooth(true);
       _goodByeTexture.setSmooth(true);
   }
}

void    Interface::loadSprite(void) {
    makeSprite(_backgroundSprite, _backgroundTexture, 1, 1, 0, 0);
    makeSprite(_boardGameSprite, _boardGameTexture, 1, 1, (_backgroundTexture.getSize().x - _boardGameTexture.getSize().x) / 2, (_backgroundTexture.getSize().y - _boardGameTexture.getSize().y) / 2);
    makeSprite(_whiteStone, _stoneWhiteTexture, 0.95f, 0.95f, 0, 0);
    makeSprite(_blackStone, _stoneBlackTexture, 0.95f, 0.95f, 0, 0);
    makeSprite(_goodByeSprite, _goodByeTexture, 1, 1, 0, 0);
    _whiteStone.setOrigin(_stoneWhiteTexture.getSize().x / _whiteStone.getScale().x / 2, _stoneWhiteTexture.getSize().y / _whiteStone.getScale().y / 2);
    _blackStone.setOrigin(_stoneBlackTexture.getSize().x / _blackStone.getScale().x / 2, _stoneBlackTexture.getSize().y / _blackStone.getScale().y / 2);
//    _allSprite.pop_back();
//    _allSprite.pop_back();
   DEBUG << "loadS\n";
}

void    Interface::makeSprite(Sprite &sprite, Texture &texture, float sizeX, float sizeY, int posX, int posY) {
    sprite.setTexture(texture);
    sprite.setScale(sizeX, sizeY);
    sprite.setPosition(posX, posY);
}

Interface::~Interface() {

}

//TO-DO : a changer, utiliser une Enum
void    Interface::setState(State newState)
{
    if (state == PAUSE && newState != PAUSE) {
        this->state = newState;
        stopPauseScreen();
        return;
    }
    else if (state == PAUSE) {
        this->state = newState;
        startPauseScreen();
        return;
    }
    this->state = newState;
    //appel fonction clean spriteList.
    switch (state) {
            case MENU :
                menuScreen();
                break;
            case GAME :
                gameScreen();
                break;
            case SCORE :
                scoreScreen();
                break;
            case AGAIN :
                againScreen();
                break;
            case GOODBYE :
                goodByeScreen();
                break;
            case WELCOME :
                welcomeScreen();
                break;
            default :
                DEBUG << "ERROR SCREEN STATE ???";
                exit(0);
                break;
    }
}

void    Interface::startPauseScreen(void) {
    DEBUG <<" PAUSE START";
}

void    Interface::stopPauseScreen(void) {
    DEBUG <<" PAUSE STOP";
}

void    Interface::drawGame(void) {
    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        this->_window.draw(*it);
    }
}

//TO-DO :
void    Interface::cleanSpriteList(void) {

    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        it = _allSprite.erase(it);
    }

//    _allSprite.erase(_allSprite.begin(), _allSprite.end());
}

void    Interface::welcomeScreen(void) {
    //cleanSpriteList();
    //add push_back list les éléments
    //set status
    _allSprite.push_back(_goodByeSprite);
    this->state = WELCOME;
    DEBUG << "WELCOME SCREEN\n";
    update();
    sleep(1);
}

void    Interface::goodByeScreen(void) {
    DEBUG << "GOODBYE SCREEN\n";
    this->cleanSpriteList();
    _allSprite.push_back(_goodByeSprite);
    //add push_back list les éléments
    this->state = GOODBYE;
}

void    Interface::menuScreen(void) {
    //cleanSpriteList();
    //add push_back list les éléments
    ////this->setScreenStatus("inMenu");
}
void    Interface::againScreen(void) {
    //cleanSpriteList();
    //add push_back list les éléments
}

void    Interface::gameScreen(void) {
    DEBUG << "GAME SCREEN\n";
    this->cleanSpriteList();
    _allSprite.push_back(_backgroundSprite);
    _allSprite.push_back(_boardGameSprite);
    this->state = GAME;
    DEBUG << "GAMEOUT SCREEN\n";
    //add push_back list les éléments
}

void    Interface::scoreScreen(void) {
    //cleanSpriteList();
    //add push_back list les éléments
}

void    Interface::timer(void) {

}

void    Interface::captureZone(void) {

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
                gomoku->end();
                break;
            case Event::KeyPressed :
            {
                switch (_event.key.code)
                {
                    case Keyboard::Escape :
                        gomoku->end();
                        break;
                    case Keyboard::Q :
                        gomoku->end();
                        break;
                    default :
                        break;
                }
            }
            break;
/*            case Event::MouseMoved :
            {
                //clickX = _event.mouseMove.x;
                //clickY = _event.mouseMove.y;
            }
            break;
*/          case Event::MouseButtonPressed :
            {
                switch (_event.mouseButton.button)
                {
                    case Mouse::Left :
                        this->checkClickLeft(current, _event.mouseButton.x, _event.mouseButton.y);
                        DEBUG << "click : xy(" <<_event.mouseButton.x << "," << _event.mouseButton.y << ")\n"; 
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
    if (state == GAME)
    {
        if (onBoard(x, y))
            this->setStoneOnClick(current, x, y);
        else
            DEBUG << "out of board add other feature interaction\n";
    }
    else if (state == WELCOME){
        DEBUG << "click during Welcome\n";
    }
    else if (state == MENU){
        DEBUG << "click during Menu\n";
    }
    else if (state == SCORE){
        DEBUG << "click during victory or fefeat screen\n";
    }
    else if (state == AGAIN){
        DEBUG << "click during Again\n";
    }
    else if (state == PAUSE){
        DEBUG << "click during Pause\n";
    }
    else if (state == GOODBYE){
        DEBUG << "click during End\n";
    }
    else
        DEBUG << "click during unknow state\n";
}

void    Interface::update(void) {
        this->_window.clear();
        this->drawGame();
        this->_window.display();
}
