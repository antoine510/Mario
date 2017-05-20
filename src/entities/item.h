#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "../common.h"
#include "object.h"
#include "../rectangle.h"

#define MUSHROOM_GOOD 1
#define MUSHROOM_BAD 2

class Item : public DynamicObject
{
    public:
        Item(Rectangle* rectangle, int TexID);
        virtual ~Item();

        virtual void collide(const Physic::CollisionParams* collParams, int collDirection) = 0;

    protected:
        virtual inline int textureState() = 0;
};

class Mushroom : public Item
{
    public:
        Mushroom(Rectangle* rectangle, int TexID, int mushroomType = MUSHROOM_GOOD);
        virtual ~Mushroom();

        virtual void collide(const Physic::CollisionParams* collParams, int collDirection);

        void reward(Player* player);

    protected:
        virtual inline int textureState() {return 0;}

        int m_mushroomType;
};

#endif // ITEM_H_INCLUDED
