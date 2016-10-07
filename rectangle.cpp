#include "rectangle.h"
#include "vector.h"
#include "graphics/viewport.h"
#include "graphics/renderDatas.h"

Rectangle::Rectangle(float x, float y, float w, float h, Uint8 refFrame) : m_x(x), m_y(y), m_w(w), m_h(h), m_refFrame(refFrame)
{ }

Rectangle::Rectangle(int x, int y, int w, int h, Uint8 refFrame) : m_x(float(x)), m_y(float(y)), m_w(float(w)), m_h(float(h)), m_refFrame(refFrame)
{ }

SDL_Rect Rectangle::getDrawSDLRect() const
{
    if(m_refFrame == FRAME_SCREEN) return SDL_Rect{(Sint16)m_x, (Sint16)m_y, (Uint16)m_w, (Uint16)m_h};
    return SDL_Rect{(Sint16)(m_x - Graphics::viewport->getOffset().getX()),
                      (Sint16)(SCREEN_HEIGHT + Graphics::viewport->getOffset().getY() - m_y - m_h), (Uint16)m_w, (Uint16)m_h};
}

void Rectangle::frameScreentoPhysics(float& x, float& y, float h)
{
    x = Graphics::viewport->getOffset().getX() + x;
    y = SCREEN_HEIGHT + Graphics::viewport->getOffset().getY() - y - h;
}

void Rectangle::framePhysicstoScreen(float& x, float& y, float h)
{
    x = x - Graphics::viewport->getOffset().getX();
    y = SCREEN_HEIGHT + Graphics::viewport->getOffset().getY() - y - h;
}

bool Rectangle::isInside(float X, float Y) const
{
    return (X >= m_x && X <= m_x+m_w && Y >= m_y && Y <= m_y+m_h);
}

void Rectangle::applySpeed(Vect2* speed)
{
    addXY(speed->getX() / PS, speed->getY() / PS);   /** We add the speed(pixel/s) each second**/
}

