#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "common.h"
#include "worldEntities.h"
#include "graphics/graphics.h"
#include "timer.h"

class Level
{
    public:
        Level(std::string name);
        ~Level();

        MarioMode update(KeyStates* keystates);

        inline std::string getName() const {return m_name;}

    private:
        std::string m_name;
        bool m_drawName;
        bool m_gameover;
        Timer m_gameoverTimer;
        LevelEntities* m_entities;
        int m_backgroundID;
        // In charge of Dialog

        friend void Graphics::Main::renderLevel();
};

#endif // LEVEL_H_INCLUDED
