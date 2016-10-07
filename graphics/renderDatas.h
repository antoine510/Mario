#ifndef RENDERDATAS_H_INCLUDED
#define RENDERDATAS_H_INCLUDED

#include "../common.h"
#include "textureSet.h"
#include "writing.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

namespace Graphics{

struct GfxData
{
    TextureSetHandler* textureSetHandler;
    Write* write;
    SDL_Renderer* renderer;
};
}

#endif // RENDERDATAS_H_INCLUDED
