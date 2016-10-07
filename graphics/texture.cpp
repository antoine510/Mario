#include "texture.h"

using namespace Graphics;

Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surface)
{
    init(renderer, surface);
}

Texture::Texture(SDL_Renderer* renderer, Surface* src)
{
    init(renderer, src->getSDLSurface());
}

Texture::Texture(SDL_Renderer* renderer, int w, int h)
{
    Surface* t = new Surface(w, h);
    init(renderer, t->getSDLSurface());
    delete t;
}

Texture::Texture(SDL_Renderer* renderer, std::string imgPath)
{
    Surface t = Surface(imgPath);
    init(renderer, t.getSDLSurface());
}

void Texture::init(SDL_Renderer* renderer, SDL_Surface* surface)
{
    m_texture = NULL;
    m_renderer = renderer;
    if(m_renderer && surface) {
        m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if(!m_texture) std::cout << "Failed to create texture :" << SDL_GetError() << std::endl;
        m_rect.w = surface->w;
        m_rect.h = surface->h;
    }
}

void Texture::blit(const Rectangle* rect)
{
    if(rect->getW() && rect->getH()) {
        SDL_Rect t = rect->getDrawSDLRect();
        SDL_Rect tClip = {0, getH() - t.h, t.w, t.h};
        SDL_RenderCopy(m_renderer, m_texture, &tClip, &t);
    }
    else {
        Rectangle tRect = *rect;
        tRect.setWH(getW(), getH());
        SDL_Rect t = tRect.getDrawSDLRect();
        SDL_RenderCopy(m_renderer, m_texture, NULL, &t);
    }
}

void Texture::rawBlitCliped(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint16 clipH)
{
    SDL_Rect t = {x, y, w, h};
    SDL_Rect tClip = {0, clipH, w, h};
    SDL_RenderCopy(m_renderer, m_texture, &tClip, &t);
}

void Texture::rawBlit(Sint16 x, Sint16 y)
{
    SDL_Rect t = {x, y, getW(), getH()};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &t);
}

//Working
void Texture::setfromSDLSurface(SDL_Surface* surface)
{
    SDL_DestroyTexture(m_texture);
    init(m_renderer, surface);
}

//Working
Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}
