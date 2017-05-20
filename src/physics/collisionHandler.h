#ifndef COLLISIONHANDLER_H_INCLUDED
#define COLLISIONHANDLER_H_INCLUDED

#include "../common.h"
#include "phyStack.h"

#define MAX_COLLISION_COUNT 16

class CollisionHandler
{
    public:
        CollisionHandler(DynamicObject* parent);
        ~CollisionHandler();

        inline void addCollision(const Physic::CollisionParams& collParams, int direction)
        {m_collParams[m_collsCount] = &collParams; m_direction[m_collsCount] = direction; m_collsCount++;}

        inline void reset() {m_maxCountThisFrame = m_collsCount; m_collsCount = 0;}

        void process();
        bool upAndDownTest();

    private:
        DynamicObject* m_parent;

        const Physic::CollisionParams* m_collParams[MAX_COLLISION_COUNT];
        int m_direction[MAX_COLLISION_COUNT];

        unsigned char m_collsCount;
        unsigned char m_maxCountThisFrame;
};

#endif // COLLISIONHANDLER_H_INCLUDED
