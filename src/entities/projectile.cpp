#include "projectile.h"
#include "../rectangle.h"
#include "../vector.h"
#include "entitiesHandler.h"

Projectile::Projectile(Rectangle& rect, const Vect2& speed, int direction)
            : DynamicObject(new Rectangle(rect.getX(), rect.getY()+10, 8, 8), 9)    //Projectile texID is always 9 : fireball
{
    m_type = TINDEX_PROJECTILE;
    m_collideWith = ENTMASK_S_AND_D ^ ENTMASK_PLAYER;
    if(direction == HDIRECTION_R) { m_speed = Vect2(200, 100); }
    else { m_speed = Vect2(-200, 100); }
    m_speed += speed;
    m_collisionCount = 0;
}

void Projectile::update()
{
    if(m_collisionCount > PROJECTILE_LIFETIME) destroy();
    DynamicObject::update();
}

void  Projectile::collide(const Physic::CollisionParams* collParams, int collDirection)
{
    if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_STATIC))
    {
        if(collDirection == DIRECTION_DOWN || collDirection == DIRECTION_UP) {
            int t = int(m_speed.getY());
            stop(collParams->static_.rect, collDirection);
            m_speed.setY(-t);
        }
        else {
            int t = int(m_speed.getX());
            stop(collParams->static_.rect, collDirection);
            m_speed.setX(-t);
        }
        m_collisionCount++;
    }
    else if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_ENEMY))
    {
        destroy();
    }
}

