#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "common.h"
#include "vector.h"
#include <cmath>

class Path1D
{
    public:
        Path1D() {}
        Path1D(PathType type, float start, float length) {initialize(type, start, length);}

        inline static float linear(float x) {return x;}
        inline static float squared(float x) {return x*x;}
        inline static float amortized(float x) {return sin(x*HALF_PI);}

        inline float getValue(float x) const {return m_start + m_length*m_f(x);}
        inline void setDest(float dest) {m_length = dest - m_start;}

    private:
        void initialize(PathType type, float start, float length);

        float (*m_f)(float);
        float m_start, m_length;
};

class Path2D
{
    public:
        Path2D() {}
        Path2D(PathType xType, PathType yType, Vect2 start, Vect2 length) {initialize(xType, yType, start, length);}
        Path2D(PathType type, Vect2 start, Vect2 length) {initialize(type, type, start, length);}

        inline Vect2 getValue(float x) const {return Vect2(m_xPath.getValue(x),m_yPath.getValue(x));}
        inline Path1D& getXPath() {return m_xPath;}
        inline Path1D& getYPath() {return m_yPath;}

        inline void setDest(const Vect2& dest) {m_xPath.setDest(dest.getX()); m_yPath.setDest(dest.getY());}

    private:
        void initialize(PathType xType, PathType yType, Vect2 start, Vect2 length);

        Path1D m_xPath, m_yPath;
};

#endif // PATH_H_INCLUDED
