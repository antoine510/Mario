#include "collisionHandler.h"
#include "../entities/object.h"
#include "../entities/entitiesHandler.h"

using namespace Physic;

CollisionHandler::CollisionHandler(DynamicObject* parent)
{
    m_parent = parent;
    m_collsCount = 0;
    m_maxCountThisFrame = 0;
}

void CollisionHandler::process()
{
    m_maxCountThisFrame = m_collsCount;
    while(m_collsCount > 0)
    {
        m_collsCount--;

        m_parent->collide(m_collParams[m_collsCount], m_direction[m_collsCount]);
    }
}

bool CollisionHandler::upAndDownTest()
{
    if(m_maxCountThisFrame < 2) return false;
    int downCount = 0;
    for (int i = 0; i < m_maxCountThisFrame; i++)
    {
        if(EntitiesHandler::matchMasks(*m_collParams[i]->static_.type, TINDEX_STATIC))
        {
            if(m_direction[i] == DIRECTION_DOWN) downCount++;
        }
    }
    return (downCount > 1);
}

CollisionHandler::~CollisionHandler()
{
}
