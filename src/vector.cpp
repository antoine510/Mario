#include "vector.h"
#include <cstdlib>

Vect2::Vect2(float X, float Y) : m_X(X), m_Y(Y)
{ }

Vect2::Vect2(int X, int Y) : m_X(float(X)), m_Y(float(Y))
{ }

Vect2 Vect2::operator=(const Vect2& other)
{
    m_X = other.getX();
    m_Y = other.getY();
    return *this;
}

Vect2 Vect2::operator+(const Vect2& other)
{
    return Vect2(m_X + other.getX(), m_Y + other.getY());
}

Vect2 Vect2::operator-(const Vect2& other)
{
    Vect2 vector(m_X - other.getX(), m_Y - other.getY());
    return vector;
}

void Vect2::operator+=(const Vect2& other)
{
    *this = *this + other;
}

bool Vect2::operator==(const Vect2& other)
{
    if ((m_X != other.getX()) || (m_Y != other.getY()))
        return false;

    return true;
}

bool Vect2::operator>=(const Vect2& other)
{
    return (getSqrLength() >= other.getSqrLength());
}

Vect2 Vect2::operator*(const float factor)
{
    m_X *= factor;
    m_Y *= factor;
    return *this;
}

Vect2::~Vect2()
{

}

Vect2i::Vect2i(int X, int Y)
{
    m_X = X;
    m_Y = Y;
}

bool Vect2i::operator!=(const Vect2i& other)
{
    if ((m_X != other.getX()) || (m_Y != other.getY()))
        return true;

    return false;
}

Vect2i::~Vect2i()
{

}

