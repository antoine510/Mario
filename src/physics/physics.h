#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "../common.h"

namespace Physic
{
    void processCollisions();
    void setMyStaticColls(int myStackPos);

    bool overlapTest(Rectangle* rectA, Rectangle* rectB);
    int staticDirectionTest(Rectangle* rectA, Rectangle* rectB, Vect2& velocityA);
    int dynamicDirectionTest(Rectangle* rectA, Rectangle* rectB, Vect2& velocityA, Vect2& velocityB);

    void staticCollision(const CollisionParams& dynamicParams, const CollisionParams& staticParams);
    void dynamicCollision(const CollisionParams& dynamicParams, const CollisionParams& dynamicParams2);
}


#endif // PHYSICS_H_INCLUDED
