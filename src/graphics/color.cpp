#include "color.h"

using namespace Graphics;

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    setColor(r, g, b, a);
}

Color::Color(const int flag)
{
    setColor(flag);
}

void Color::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    m_r = r; m_g = g; m_b = b; m_a = a;
}

void Color::setColor(const int flag)
{
    switch (flag)
    {
        case COLOR_BLACK:
            m_r = 0, m_g = 0, m_b = 0; m_a = 255;
            break;
        case COLOR_WHITE:
            m_r = 255, m_g = 255, m_b = 255; m_a = 255;
            break;
        case COLOR_SKY:
            m_r = 130, m_g = 200, m_b = 255; m_a = 255;
            break;
        case COLOR_COIN_TEXT:
            m_r = 200, m_g = 200, m_b = 200; m_a = 255;
            break;
        default:
            break;
    }
}

SDL_Color Color::getSDLColor() const
{
    SDL_Color col = {m_r, m_g, m_b, m_a};
    return col;
}

Color Color::operator=(const int flag)
{
    setColor(flag);
    return *this;
}

