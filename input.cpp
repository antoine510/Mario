#include "input.h"

void KeyStates::refresh()
{
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    SDL_PumpEvents();
    keystates = SDL_GetKeyboardState(NULL);
}

void KeyStates::mouseWheelIncrement(int* value) const
{
    SDL_Event event;
    bool wheelMoved = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL) != 0;
    if(wheelMoved) (*value) += event.wheel.y;
}

bool KeyStates::isMouse(Uint32 type, Uint8 subType) const
{
    SDL_Event event;
    bool mouseActive = SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, type, type) != 0;
    return mouseActive && (event.button.button == subType);
}
