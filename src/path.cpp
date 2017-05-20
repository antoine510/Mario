#include "path.h"

void Path1D::initialize(PathType type, float start, float length)
{
    switch (type)
    {
        case LINEAR:
            m_f = linear;
            break;
        case SQUARED:
            m_f = squared;
            break;
        case AMORTIZED:
            m_f = amortized;
            break;
    }
    m_start = start;
    m_length = length;
}

void Path2D::initialize(PathType xType, PathType yType, Vect2 start, Vect2 length)
{
    m_xPath = Path1D(xType, start.getX(), length.getX());
    m_yPath = Path1D(yType, start.getY(), length.getY());
}

