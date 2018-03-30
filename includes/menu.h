#ifndef MENU_H
# define MENU_H

# include "player.h"
# include "utils.h"
class Interface;

# define XBOX_START 410
# define XBOX_END 750
# define XBOX_MIDDLE 575
# define YBOX_VARIANTE_MIDDLE 355
# define YBOX_P1_MIDDLE 465
# define YBOX_P2_MIDDLE 580
# define VARIANTE_UP 310
# define P1_UP 425
# define P2_UP 540
# define GO_UP 650
# define VARIANTE_DOWN 410
# define P1_DOWN 520
# define P2_DOWN 630
# define GO_DOWN 750

typedef enum textChoice {
    HUMAN, RANDOM, IA_HARD, IA_NORMAL, IA_EASY, CLASSIQUE, NOTHING = 0
} TextChoice;

class Menu {

    friend class Interface;

    private:
        sf::Font            arial;
        void    setTextString(sf::Text &text, TextChoice &textChoice);
        //int     searchPosX(unsigned int strLen);
        void    setMiddle(sf::Text &Text);

        sf::Sprite			backgroundMenuSprite;
		sf::Texture			backgroundMenuTexture;
		
        /*sf::Sprite          boxVariante;
		sf::Sprite			boxP1;
		sf::Sprite			boxP2;
		sf::Sprite			boxGo;*/

    protected:
		sf::Text            textBoxVariante;
		sf::Text			textBoxP1;
		sf::Text			textBoxP2;
        //Rules *upadteRules(Rules *rules); // si variante
        Player *updatePlayer(TextChoice &textChoice);
        void    switchTextBox(sf::Text &text, TextChoice &textChoice);
        void    updateText(sf::Text &text, TextChoice &textChoice);
        void    go(Gomoku* gomoku);
        TextChoice  choiceP1;
        TextChoice  choiceP2;
        TextChoice  variante;
        bool    onP1(int x, int y);
        bool    onP2(int x, int y);
        bool    onVariante(int x, int y);
        bool    onGo(int x, int y);



    public:
        Menu();
        ~Menu();
};

#endif