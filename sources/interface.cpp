#include "interface.h"
#include "gomoku.h"
#include "player.h"
#include "rules.h"
#include "utils.h"
#include "menu.h"

using namespace sf;

Interface::Interface() : _window(sf::VideoMode(WIDTH, HEIGHT), "GOMOKU", Style::Titlebar | Style::Close)
{
   _window.setFramerateLimit(60);
   _window.setVerticalSyncEnabled(true);
   this->loadTexture();
   this->loadSprite();
   initCoordBoard();
   initCoordCanteen();
   this->setState(WELCOME);
   previewStone = false;
   DEBUG << "INTERFACE READY\n";
}

Interface::~Interface() {

}

//TO-DO : Ajout texture des autres States ici.
void    Interface::loadTexture(void) {
   if(!_stoneWhiteTexture.loadFromFile("./sprite/whiteStone.png")
    || !_stoneBlackTexture.loadFromFile("./sprite/blackStone.png")
    || !_backgroundTexture.loadFromFile("./sprite/background.png")
    || !_boardGameTexture.loadFromFile("./sprite/goban(2).png")
    || !_helloTexture.loadFromFile("./sprite/hello.png")
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
       _helloTexture.setSmooth(true);
   }
}

void    Interface::loadSprite(void) {
    makeSprite(_backgroundSprite, _backgroundTexture, 1, 1, 0, 0);
    makeSprite(_boardGameSprite, _boardGameTexture, 0.9f, 0.9f, (_backgroundTexture.getSize().x - (_boardGameTexture.getSize().x * 0.9)) / 2, (_backgroundTexture.getSize().y - (_boardGameTexture.getSize().y * 0.9)) / 2);
    makeSprite(_whiteStone, _stoneWhiteTexture, 0.825f, 0.825f, 0, 0);
    makeSprite(_blackStone, _stoneBlackTexture, 0.825f, 0.825f, 0, 0);
    makeSprite(_goodByeSprite, _goodByeTexture, 1, 1, 0, 0);
    makeSprite(_helloSprite, _helloTexture, 1, 1, 0, 0);
    makeSprite(previewStoneFree, _stoneWhiteTexture,0.825f, 0.825f, 0, 0);
    makeSprite(previewStoneForbidden, _stoneWhiteTexture,0.825f, 0.825f, 0, 0);
    _whiteStone.setOrigin(_stoneWhiteTexture.getSize().x / _whiteStone.getScale().x / 2, _stoneWhiteTexture.getSize().y / _whiteStone.getScale().y / 2);
    _blackStone.setOrigin(_stoneBlackTexture.getSize().x / _blackStone.getScale().x / 2, _stoneBlackTexture.getSize().y / _blackStone.getScale().y / 2);
    previewStoneFree.setOrigin(_stoneWhiteTexture.getSize().x / _whiteStone.getScale().x / 2, _stoneWhiteTexture.getSize().y / _whiteStone.getScale().y / 2);
    previewStoneForbidden.setOrigin(_stoneBlackTexture.getSize().x / _blackStone.getScale().x / 2, _stoneBlackTexture.getSize().y / _blackStone.getScale().y / 2);
    previewStoneFree.setColor(Color(0,255,0,125));
    previewStoneForbidden.setColor(Color(255,0,0,125));
    //    _allSprite.pop_back();
//    _allSprite.pop_back();
   DEBUG << "SPRITES LOADS\n";
}

void    Interface::makeSprite(Sprite &sprite, Texture &texture, float sizeX, float sizeY, int posX, int posY) {
    sprite.setTexture(texture);
    sprite.setScale(sizeX, sizeY);
    sprite.setPosition(posX, posY);
}

void    Interface::initCoordBoard(void) {
    int i = 0;
    int j = 0;
    float step = 40.0f;//(float)((BOARD_RIGHT - BOARD_LEFT) / 18);
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
    float step = 40.0f;//(float)((BOARD_RIGHT - BOARD_LEFT) / 18);
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
    Vector2<int> tmp = turnCoordInterfaceInGomokuBoardIndex(clickx, clicky);
    if (tmp.x == -1)
        return;
    if (gomoku->getRules().canPutStone(current, tmp.x, tmp.y)) {
        current.setCoordPlayed(tmp.x, tmp.y);
        current.setPlayed(true);
    }
}

Vector2<int>    Interface::turnCoordInterfaceInGomokuBoardIndex(int mouseX, int mouseY) {
    int i = 0;
    int j = 0;
    Vector2<int> tmp;
    while (i < GW) {
        j = 0;
        while (j < GH) {
            if (mouseX <= coordBoard[i][j].x + CENTER_MAX_DISTANCE && mouseX >= coordBoard[i][j].x - CENTER_MAX_DISTANCE &&
                mouseY <= coordBoard[i][j].y + CENTER_MAX_DISTANCE && mouseY >= coordBoard[i][j].y - CENTER_MAX_DISTANCE) {
                tmp.x = i;
                tmp.y = j;
                return (tmp); 
                }
            j++;
            }
        i++;
    }
    tmp.x = -1;
    tmp.y = -1;
    return (tmp); 
}

void	Interface::capture(Player &current, sf::Sprite *spriteEnemy, int x1, int y1) {
    int i = getCoordBoard(x1,y1).x;
    int j = getCoordBoard(x1,y1).y;
    removeStone(i,j);
    this->putStone(*spriteEnemy, current.getCoordCanteen(current.getNbCapture() - 1).x, current.getCoordCanteen(current.getNbCapture() - 1).y);
}

void    Interface::removeStone(int i, int j) {
    Vector2<int> pos;
    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        pos = (Vector2<int>)(*it).getPosition();
        if ((pos.x == i && pos.y == j)){
            it = _allSprite.erase(it);
            DEBUG << "REMOVE\n";
            break;
        }
    }
}

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
    this->cleanInterface();
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
    this->update();
    }
}

void    Interface::startPauseScreen(void) {
    DEBUG <<" PAUSE START";
}

void    Interface::stopPauseScreen(void) {
    DEBUG <<" PAUSE STOP";
}

void    Interface::drawGame(void) {
    //Affichage des sprites en premier:
    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        this->_window.draw(*it);
    }
    //Affichage des textes par dessus :
    for (std::list<Text*>::iterator it = _allText.begin(); it != _allText.end(); it++) {
        this->_window.draw(*(*it));
    }
}

void    Interface::cleanInterface(void) {
    this->cleanSpriteList();
    this->cleanTextList();
}

void    Interface::cleanTextList(void) {
    for (std::list<Text*>::iterator it = _allText.begin(); it != _allText.end(); it++) {
        it = _allText.erase(it);
    }
}

void    Interface::cleanSpriteList(void) {
    for (std::list<Sprite>::iterator it = _allSprite.begin(); it != _allSprite.end(); it++) {
        it = _allSprite.erase(it);
    }
//    _allSprite.erase(_allSprite.begin(), _allSprite.end());
}

void    Interface::welcomeScreen(void) {
    _allSprite.push_back(_helloSprite);
    this->state = WELCOME;
    DEBUG << "WELCOME SCREEN\n";
    update();
    sleep(1);
}

void    Interface::goodByeScreen(void) {
    DEBUG << "GOODBYE SCREEN\n";
    _allSprite.push_back(_goodByeSprite);
    this->state = GOODBYE;
}

void    Interface::menuScreen(void) {
    _allSprite.push_back(menu.backgroundMenuSprite);
    _allText.push_back(&menu.textBoxP1);
    _allText.push_back(&menu.textBoxP2);
    _allText.push_back(&menu.textBoxVariante);
    this->state = MENU;
}

void    Interface::againScreen(void) {
    //cleanSpriteList();
    //add push_back list les éléments
}

void    Interface::gameScreen(void) {
    _allSprite.push_back(_backgroundSprite);
    _allSprite.push_back(_boardGameSprite);
    this->state = GAME;
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

void    Interface::putPreviewStone(Player &current, int mouseX, int mouseY)
{
    Vector2<int> tmp = turnCoordInterfaceInGomokuBoardIndex(mouseX, mouseY);
    if (tmp.x == -1)
        return;
    Vector2<int> coord = getCoordBoard(tmp.x, tmp.y);
    if (gomoku->getStone(tmp.x, tmp.y) == FREE) {
        if ((gomoku->getRules()).canPutStone(current, tmp.x, tmp.y)) {
            this->putStone(this->previewStoneFree, coord.x, coord.y);
        }
        else {
            this->putStone(this->previewStoneForbidden, coord.x, coord.y);
        }
        this->previewStone = true;
        this->coordPreviewStone.x = coord.x;
        this->coordPreviewStone.y = coord.y;
    }
}

void    Interface::unputPreviewStone(int mouseX, int mouseY) {
        if (!this->previewStone)
            return;
        Vector2<int> tmp = turnCoordInterfaceInGomokuBoardIndex(mouseX, mouseY);
        if (tmp.x == -1)
            return;
        Vector2<int> coord = getCoordBoard(tmp.x, tmp.y);
        if (coord.x != coordPreviewStone.x || coord.y != coordPreviewStone.y) {
            this->previewStone = false;
            removeStone(this->coordPreviewStone.x, this->coordPreviewStone.y);
            this->coordPreviewStone.x = -1;
            this->coordPreviewStone.y = -1;
        }
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
            case Event::MouseMoved :
            {
                if (state == GAME) {
                    int x = _event.mouseMove.x;
                    int y = _event.mouseMove.y;
                    if (onBoard(x,y)) {
                        if (!previewStone) {
                            putPreviewStone(current, x, y);
                            update();
                        }
                        else
                            unputPreviewStone(x, y);

                    }
                    else if (previewStone)
                        unputPreviewStone(x, y);
                }
            }
            break;
            case Event::MouseButtonPressed :
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
        if (menu.onP1(x, y))
        {
            menu.switchTextBox(menu.textBoxP1, menu.choiceP1);
        }
        else if (menu.onP2(x, y))
        {
            menu.switchTextBox(menu.textBoxP2, menu.choiceP2);
        }
        else if (menu.onVariante(x, y))
        {
            menu.switchTextBox(menu.textBoxVariante, menu.variante);
        }
        else if (menu.onGo(x, y)){
            menu.go(gomoku);//setPlayer...
            setState(GAME);
        }
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
