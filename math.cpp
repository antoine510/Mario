#include "math.h"

Uint16 log2i(unsigned int x)
{
    Uint16 resu = 0;
    while (x>1)
    {
        x = x/2;
        resu += 1;
    }
    return resu;
}
