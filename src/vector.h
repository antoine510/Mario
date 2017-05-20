#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "common.h"

#define DIRECTION_NONE 0
#define DIRECTION_RIGHT 1
#define DIRECTION_UP 2
#define DIRECTION_LEFT 3
#define DIRECTION_DOWN 4

#define HDIRECTION_R 0
#define HDIRECTION_L 1

#define GRAVITY 600.0

#define PI 3.1415926536f
#define HALF_PI 1.5707963268f

class Vect2
{
    public:
        Vect2(float X = 0, float Y = 0);
		explicit Vect2(int X, int Y);
        ~Vect2();

        inline void setX(float X) {m_X = X;}
		inline void setX(int X) { m_X = float(X); }
        inline void setY(float Y) {m_Y = Y;}
		inline void setY(int Y) { m_Y = float(Y); }
        inline void setXY(float X, float Y) {m_X = X; m_Y = Y;}
		inline void setXY(int X, int Y) { m_X = float(X); m_Y = float(Y); }

        inline void addX(float X) {m_X += X;}
        inline void addY(float Y) {m_Y += Y;}

        inline void subAbsX(float X) {(m_X<0 ? m_X += X : m_X -= X);}

        inline float getX() const {return m_X;}
        inline float getAbsX() const {return (m_X<0 ? -m_X : m_X);}
        inline float getY() const {return m_Y;}
        inline float getSqrLength() const {return m_X*m_X + m_Y*m_Y;}

        inline static int invDirection(int direction) {return ((direction+1)%4)+1;}
        inline static char forwardMulti(int direction) {return 2-direction;}

        inline void integrate(float aX, float aY) {m_X += aX/PS; m_Y += aY/PS;}

        Vect2 operator+(const Vect2& other);
        void operator+=(const Vect2& other);
        Vect2 operator-(const Vect2& other);
        Vect2 operator=(const Vect2& other);
        bool operator==(const Vect2& other);
        bool operator>=(const Vect2& other);
        Vect2 operator*(const float factor);

    private:
        float m_X;
        float m_Y;

};

class Vect2i
{
    public:
        Vect2i(int X = 0, int Y = 0);
        ~Vect2i();

        inline void setX(int X) {m_X = X;}
        inline void setY(int Y) {m_Y = Y;}
        inline void setXY(int X, int Y) {m_X = X; m_Y = Y;}

        inline void addX(int X) {m_X += X;}
        inline void addY(int Y) {m_Y += Y;}

        inline int getX() const {return m_X;}
        inline int getY() const {return m_Y;}

        bool operator!=(const Vect2i& other);
        Vect2i operator+(const Vect2i& other) {return Vect2i(m_X + other.getX(), m_Y + other.getY());}
        Vect2i operator-(const Vect2i& other) {return Vect2i(m_X - other.getX(), m_Y - other.getY());}
        Vect2i operator*(const float factor) {return Vect2i(int(m_X*factor), int(m_Y*factor));}

    private:
        int m_X;
        int m_Y;

};

#endif // VECTOR_H_INCLUDED
