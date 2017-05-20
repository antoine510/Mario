#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include <SDL.h>
#include "../common.h"
#include "color.h"
#include "../rectangle.h"

namespace Graphics{

class Surface
{
    public:
        Surface(int w, int h);
        Surface(std::string imgPath);
        ~Surface();

        void fillColor(Color color);

        Surface* getSubSurface(Rectangle clipRect);

        inline SDL_Surface* getSDLSurface() const {return m_surface;}
        inline int getW() const {return m_surface->w;}
        inline int getH() const {return m_surface->h;}
        inline void setColorKey() {SDL_SetColorKey(m_surface, SDL_TRUE, SDL_MapRGB(m_surface->format, 0, 255, 0));}

    private:
        SDL_Surface* m_surface;
};
}

#endif // SURFACE_H_INCLUDED
