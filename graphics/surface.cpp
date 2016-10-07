#include "surface.h"
#include <SDL_image.h>

using namespace Graphics;

Surface::Surface(int w, int h)
{
    m_surface = SDL_CreateRGBSurface(0, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if(!m_surface) std::cerr << "Unable to create surface : " << SDL_GetError() << std::endl;
}

Surface::Surface(std::string imgPath)
{
    m_surface = IMG_Load(imgPath.c_str());
    if (!m_surface) std::cerr << "Couldn't find " << imgPath;
    setColorKey();
}

void Surface::fillColor(Color color)
{
    SDL_FillRect(m_surface, NULL, color.getMappedColor(m_surface->format));
}

Surface* Surface::getSubSurface(Rectangle clipRect)
{
    Surface* resu = new Surface(clipRect.getW(), clipRect.getH());
    SDL_SetColorKey(m_surface, SDL_FALSE, 0);

    SDL_Rect trect = clipRect.getSDLRect();
    SDL_BlitSurface(m_surface, &trect, resu->getSDLSurface(), NULL);
    resu->setColorKey();
    return resu;
}

Surface::~Surface()
{
    SDL_FreeSurface(m_surface);
}

