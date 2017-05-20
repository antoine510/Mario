#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "common.h"
#include "graphics/graphics.h"

class Menu
{
    public:
        Menu(Level** level);
        ~Menu();

        void readMenuFile();

        MarioMode update(KeyStates* keystates); // Returns the main mode selected in menu

    private:
        MarioMode selectButton();
        void resetMode(MenuMode mode);

        unsigned int m_selection;
        bool m_keyPressed;

        MenuMode m_mode;
        bool m_editing;

        int m_oldMouseX, m_oldMouseY;

        std::vector< std::vector<Button*> > m_buttons;
        std::vector<std::string> m_levelNames;

        Level** m_currentLevel;

        friend void Graphics::Main::renderMenu(Menu*);
};

#endif // MENU_H_INCLUDED
