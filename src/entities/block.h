#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "../common.h"

#include "object.h"
#include "../rectangle.h"

class Block : public StaticObject
{
    public:
        Block(Rectangle* rectangle, int TexID);
        ~Block();

    protected:
        inline virtual int textureState() {return 0;}
};

class Brick : public Block
{
    public:
        Brick(Rectangle* rectangle, int TexID);

    protected:

};

class Switch : public Block
{
    public:
        Switch(Rectangle* rectangle, int TexID);

    protected:

};

#endif // BLOCK_H_INCLUDED
