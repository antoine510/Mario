#ifndef MARIO_H_INCLUDED
#define MARIO_H_INCLUDED

#include "common.h"

/**Deals with the multiple definition error**/

class Mario
{
    public:
        Mario();
        ~Mario();

        void loop();
        void exit(bool value);

    private:
        Graphics::Main* m_graphics;
        Sound* m_sound;
        KeyStates* m_keystates;
        Level* m_level;
        Menu* m_menu;
        Editor* m_editor;

        MarioMode m_mode;
};

#endif // MARIO_H_INCLUDED
