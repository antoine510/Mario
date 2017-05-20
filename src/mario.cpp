#include "mario.h"
#include "graphics/graphics.h"
#include "sound.h"
#include "input.h"
#include "level.h"
#include "menu.h"
#include "editor.h"
#include "timer.h"
#include <SDL_image.h>

void Mario::loop()
{
    #ifndef DEBUG
    const unsigned int totTime = (1000 / FPS);
    unsigned int initTime;
    #endif


    //Event loop

    do
    {
        #ifndef DEBUG
        initTime = SDL_GetTicks();
        #endif

        m_keystates->refresh();
        timerStack->updateTimers();

        if(m_mode == MODE_LEVEL)
        {
            m_mode = m_level->update(m_keystates);
            m_graphics->renderLevel();
        }
        else if(m_mode == MODE_MENU)
        {
            m_mode = m_menu->update(m_keystates);
            m_graphics->renderMenu(m_menu);
        }
        else if(m_mode == MODE_EDITOR)
        {
            m_mode = m_editor->update(m_keystates);
            m_graphics->renderEditor(m_editor);
        }

        m_sound->playAll();
        m_graphics->updateScreen();


        //Speed limit
        #ifndef DEBUG
        SDL_Delay(totTime + SDL_GetTicks() - initTime);
        #else
        SDL_Delay(16);
        #endif
    } while (!m_keystates->isEsc() && m_mode != MODE_QUIT);

}

Mario::Mario()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        std::cerr << "Failed to initialize SDL : " << SDL_GetError();
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL_image : " << IMG_GetError();
    }

    timerStack = new TimerStack;
    m_graphics = new Graphics::Main;
    m_sound = new Sound;
    m_keystates = new KeyStates;
    m_level = NULL;
    m_menu = new Menu(&m_level);
    m_editor = new Editor(&m_level);

    m_mode = MODE_MENU;
    std::cout << std::endl << "Initialization complete" << std::endl;
}

Mario::~Mario()
{
    delete m_editor;
    delete m_menu;                  //Mind the fact that destructor order matters !
    delete m_level;
    delete m_keystates;
    delete m_sound;
    delete m_graphics;
    delete timerStack;

    IMG_Quit();
    SDL_Quit();
    std::cout << "Deletion complete" << std::endl;
}


//      Entry point of the program
int main ( int argc, char** argv )
{
    Mario mario;
    mario.loop();

    return 0;
}

