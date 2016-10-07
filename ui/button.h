#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "../common.h"
#include "../rectangle.h"
#include "../graphics/graphics.h"

enum ButtonState {UNSELECTED = 0, SELECTED = 1};

class Button
{
    public:
        Button(int x, int y, int texID);
        ~Button();

        inline int getTexID() const {return m_texID;}
        inline int getState() const {return m_state;}
        inline void setState(ButtonState newState) {m_state = newState;}
        inline bool isValid() const {return (m_rectangle.getW() != 0 && m_rectangle.getH() != 0);}
        inline Rectangle& getRect() {return m_rectangle;}

    private:
        Rectangle m_rectangle;
        ButtonState m_state;
        int m_texID;

        friend void Graphics::Main::renderButton(Button*);
};

#endif // BUTTON_H_INCLUDED
