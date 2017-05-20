#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "common.h"
#include <SDL.h>

#define FRAME_SCREEN 0
#define FRAME_PHYSICS 1

class Vect2;

class Rectangle
{
    public:
        Rectangle(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f, Uint8 refFrame = 1);
		Rectangle(int x, int y, int w = 0, int h = 0, Uint8 refFrame = 1);

        inline void setX(float x)   {m_x = x; }
		inline void setX(int x)		{ m_x = float(x); }
        inline void setY(float y)   {m_y = y; }
		inline void setY(int y)		{ m_y = float(y); }
        inline void setXY(float x, float y)   {m_x = x; m_y = y; }
		inline void setXY(int x, int y) { m_x = float(x); m_y = float(y); }
        inline void setW(float w)   {m_w = w; }
		inline void setW(int w) { m_w = float(w); }
        inline void setH(float h)   {m_h = h; }
		inline void setH(int h) { m_h = float(h); }
        inline void setWH(float w, float h) {m_w=w; m_h=h;}
		inline void setWH(int w, int h) { m_w = float(w); m_h = float(h); }
        inline void addXY(float x, float y)   {m_x += x; m_y += y; }
        inline void addX(float x)   {m_x += x; }
		inline void addX(int x) { m_x += float(x); }
        inline void addY(float y)   {m_y += y; }
		inline void addY(int y) { m_y += float(y); }
        inline void addW(float w)   {m_w += w; }
        inline void addH(float h)   {m_h += h; }

        inline int getX() const   {return (int)m_x;}
        inline float* getXptr() {return &m_x;}
        inline int getY() const   {return (int)m_y;}
        inline int getW() const   {return (int)m_w;}
        inline int getH() const   {return (int)m_h;}

        inline int getOffsetW() const {return (int)(m_x + m_w);}
        inline int getOffsetH() const {return (int)(m_y + m_h);}
        inline float getOffsetFW() const {return m_x + m_w;}
        inline float getOffsetFH() const {return m_y + m_h;}

        inline float getFX() const   {return m_x;}
        inline float getFY() const   {return m_y;}
        inline float getFW() const   {return m_w;}
        inline float getFH() const   {return m_h;}

        inline SDL_Rect getSDLRect() const {return SDL_Rect{(Sint16)m_x, (Sint16)m_y, (Uint16)m_w, (Uint16)m_h};}
        inline Uint8 getFrame() const {return m_refFrame;}
        SDL_Rect getDrawSDLRect() const;
        inline void toFramePhysics() {frameScreentoPhysics(m_x, m_y, m_h);}
        inline void toFrameScreen() {framePhysicstoScreen(m_x, m_y, m_h);}

        static void frameScreentoPhysics(float& x, float& y, float h);
        static void framePhysicstoScreen(float& x, float& y, float h);

        void applySpeed(Vect2* speed);
        bool isInside(float X, float Y) const;
		inline bool isInside(int X, int Y) const { return isInside(float(X), float(Y)); }
        inline bool isNatural() const {return (m_w > 0 && m_h > 0);}

    private:
        float m_x;
        float m_y;
        float m_w;
        float m_h;
        Uint8 m_refFrame;
};

#endif // RECTANGLE_H_INCLUDED
