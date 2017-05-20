#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "../common.h"
#include "object.h"

#define PROJECTILE_LIFETIME 5

class Projectile : public DynamicObject
{
    public:
        Projectile(Rectangle& rect, const Vect2& speed, int direction);

        virtual void update();
        virtual void collide(const Physic::CollisionParams* collParams, int collDirection);

    protected:
        virtual int textureState() {return 100;};

        unsigned char m_collisionCount;
};

#endif // PROJECTILE_H_INCLUDED
