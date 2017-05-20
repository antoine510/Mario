#include "item.h"
#include "enemy.h"
#include "player.h"
#include "entitiesHandler.h"

Item::Item(Rectangle* rectangle, int TexID) : DynamicObject(rectangle, TexID)
{
    m_type = TINDEX_ITEM;
    m_collideWith = ENTMASK_S_AND_D ^ ENTMASK_PROJECTILE;     //Static & Dynamic
    m_speed.setX(FORWARD_SPEED);
    m_forwardDirection = 1;
}

Item::~Item()
{
}

Mushroom::Mushroom(Rectangle* rectangle, int TexID, int mushroomType) : Item(rectangle, TexID)
{
    m_mushroomType = mushroomType;
}

void Mushroom::reward(Player* player)
{
    switch(m_mushroomType)
    {
        case MUSHROOM_GOOD:
            player->addLife();
            break;
        case MUSHROOM_BAD:
            player->hurt();
            break;
    }
}

void Mushroom::collide(const Physic::CollisionParams* collParams, int collDirection)
{
    if(EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_PLAYER))
    {
        destroy();
    }
    else
    {
        goBack(collDirection);
        stop(collParams->static_.rect, collDirection);
        m_speed.setX(m_forwardDirection*FORWARD_SPEED);
    }
}

Mushroom::~Mushroom()
{
}
