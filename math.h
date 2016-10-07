#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include "common.h"

Uint16 log2i(unsigned int x);
template <class T> void clamp(T* a, T b, T c) {if(*a < b) *a=b; if(*a > c) *a=c;}

#endif // MATH_H_INCLUDED
