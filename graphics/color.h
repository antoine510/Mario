#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "../common.h"
#include <SDL.h>

#define COLOR_NONE 0
#define COLOR_BLACK 1
#define COLOR_WHITE 2
#define COLOR_SKY 3
#define COLOR_COIN_TEXT 4

namespace Graphics{
class Color
{
    public:
        Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
        Color(const int flag);

        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void setColor(const int flag);

        SDL_Color getSDLColor() const;
        inline Uint8 getR() const {return m_r;}
        inline Uint8 getG() const {return m_g;}
        inline Uint8 getB() const {return m_b;}
        inline Uint8 getA() const {return m_a;}
        inline Uint32 getMappedColor(const SDL_PixelFormat* pxFormat) const {return SDL_MapRGBA(pxFormat, m_r, m_g, m_b, m_a);}

        Color operator=(const int flag);

    private:
        Uint8 m_r, m_g, m_b, m_a;
};
}

#endif // COLOR_H_INCLUDED
