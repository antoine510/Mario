#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "common.h"
#include <SDL.h>

class KeyStates
{
    public:
        void refresh();

        inline bool isRight(unsigned char keySet =0) const {return keystates[(keySet == 0) ? SDL_SCANCODE_RIGHT : SDL_SCANCODE_L] != 0;}
        inline bool isLeft(unsigned char keySet =0) const {return keystates[(keySet == 0) ? SDL_SCANCODE_LEFT : SDL_SCANCODE_J] != 0;}
        inline bool isSpeed() const {return keystates[SDL_SCANCODE_LSHIFT] != 0;}
        inline bool isDown(unsigned char keySet =0) const {return keystates[(keySet == 0) ? SDL_SCANCODE_DOWN : SDL_SCANCODE_K] != 0;}
        inline bool isUp() const {return keystates[SDL_SCANCODE_UP] != 0;}
        inline bool isEsc() const {return keystates[SDL_SCANCODE_ESCAPE] != 0;}
        inline bool isSpace(unsigned char keySet =0) const {return keystates[(keySet == 0) ? SDL_SCANCODE_SPACE : SDL_SCANCODE_RSHIFT] != 0;}
        inline bool isFire(unsigned char keySet =0) const {return keystates[(keySet == 0) ? SDL_SCANCODE_C : SDL_SCANCODE_P] != 0;}
        inline bool isEditor() const {return keystates[SDL_SCANCODE_E] != 0;}
        inline bool isHoldEditor() {bool p = keystates[SDL_SCANCODE_E] != 0; bool h = p && !editorHold; editorHold = p; return h;}
        inline bool isHoldDelete() {bool p = keystates[SDL_SCANCODE_DELETE] != 0; bool h = p && !delHold; delHold = p; return h;}
        inline bool isMouseLeftDown() const {return isMouse(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT);}
        inline bool isMouseLeftUp() const {return isMouse(SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT);}
        inline bool isMouseMiddleDown() const {return isMouse(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_MIDDLE);}
        inline bool isMouseMiddleUp() const {return isMouse(SDL_MOUSEBUTTONUP, SDL_BUTTON_MIDDLE);}
        inline bool isMouseRightDown() const {return isMouse(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_RIGHT);}
        inline bool isMouseRightUp() const {return isMouse(SDL_MOUSEBUTTONUP, SDL_BUTTON_RIGHT);}
        void mouseWheelIncrement(int* value) const;

    private:
        bool isMouse(Uint32 type, Uint8 subType) const;

        const Uint8* keystates;
        bool editorHold, delHold;
};

#endif // INPUT_H_INCLUDED
