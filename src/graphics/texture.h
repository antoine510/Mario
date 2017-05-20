#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <SDL.h>
#include "../common.h"
#include "surface.h"
#include "../rectangle.h"

namespace Graphics{

class Texture
{
    public:
        Texture(SDL_Renderer* renderer, SDL_Surface* surface = NULL);
        Texture(SDL_Renderer* renderer, Surface* src);
        Texture(SDL_Renderer* renderer, int w, int h);
        Texture(SDL_Renderer* renderer, std::string imgPath);
        ~Texture();

        void blit(const Rectangle* rect);
        void rawBlit(Sint16 x, Sint16 y);
        void rawBlitCliped(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint16 clipH);
        inline void blitCentered(Rectangle rect) {rect.addXY(-0.5f * getW(), -0.5f * getH()); blit(&rect);}

        void setfromSDLSurface(SDL_Surface* surface);

        inline int getW() const {return m_rect.w;}
        inline int getH() const {return m_rect.h;}

    private:
        void init(SDL_Renderer* renderer, SDL_Surface* surface);

        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        SDL_Rect m_rect;
};
}

#endif // TEXTURE_H_INCLUDED
