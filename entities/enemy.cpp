#include "enemy.h"
#include "entitiesHandler.h"
#include "../sound.h"

Enemy::Enemy(Rectangle* rectangle, int TexID) : DynamicObject(rectangle, TexID), m_killTimer(1000)
{
    m_collideWith = ENTMASK_S_AND_D;         //Static & Dynamic
    m_speed.setX(FORWARD_SPEED);
    m_forwardDirection = 1;
}

void Enemy::kill()
{
    m_killTimer.start();
    DynamicObject::kill();
}

void Enemy::update()
{
    if (!m_isAlive && !m_killTimer.isRunning()) destroy();

    DynamicObject::update();
}

Enemy::~Enemy()
{
}

Goomba::Goomba(Rectangle* rectangle, int TexID) : Enemy(rectangle, TexID), m_walkTimer(WALKING_ANIMATION_SPEED)
{
    m_type = TINDEX_GOOMBA;
    m_walkTimer.start();
}

int Goomba::textureState()
{
    if (!m_isAlive) return 2;
    return (m_walkTimer.getLoopingCount() % 2) != 0;
}

void Goomba::kill()
{
    if (m_isAlive) {
        m_rectangle->addH(-8);
        m_gfxParameters.setState(textureState());
        m_gfxParameters.updateBlitRects();
    }
    Enemy::kill();
}

void Goomba::collide(const Physic::CollisionParams* collParams, int collDirection)
{
    if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_STATIC))
    {
        goBack(collDirection);
        stop(collParams->static_.rect, collDirection);
        m_speed.setX(m_forwardDirection*FORWARD_SPEED);
    }
    else
    {
        if(EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_PLAYER)) {
            if(collDirection == DIRECTION_UP) kill();
        }
        else if(EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_PROJECTILE) || collDirection == DIRECTION_UP) {
            kill();
        }
        else {
            goBack(collDirection);
            stop(collParams->static_.rect, collDirection);
            m_speed.setX(m_forwardDirection*FORWARD_SPEED);
        }
    }
}

Goomba::~Goomba()
{
}

Koopa::Koopa(Rectangle* rectangle, int TexID) : Enemy(rectangle, TexID)
{
    m_type = TINDEX_KOOPA;
    m_isShell = false;
    m_isShellMoving = true;
}

int Koopa::textureState()
{
    if (m_isShell) return 0;
    return (m_speed.getX()<0 ? 101 : 100);
}

void Koopa::collide(const Physic::CollisionParams* collParams, int collDirection)
{
    if(EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_STATIC))
    {
        stop(collParams->static_.rect, collDirection);
        if(collDirection == DIRECTION_RIGHT || collDirection == DIRECTION_LEFT)
        {
            goBack(collDirection);
            m_speed.setX((FORWARD_SPEED + KOOPA_SHELL_SPEED_BOOST * (int)m_isShell) * (int)m_isShellMoving * m_forwardDirection);
        }
    }
    else if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_PROJECTILE)) {destroy();}
    else
    {
        switch (collDirection)
        {
        case DIRECTION_UP:
            if (m_isShell && !m_isShellMoving)
            {
                m_isShellMoving = true;
                m_speed.setX((FORWARD_SPEED + KOOPA_SHELL_SPEED_BOOST) * m_forwardDirection);
            }
            else if(!m_isShell || (m_isShell && m_isShellMoving))
            {
                m_isShell = true;
                m_isShellMoving = false;
                m_rectangle->setH(14);
                m_gfxParameters.setState(textureState());
                m_gfxParameters.updateBlitRects();
                m_speed.setX(0);
            }
            break;
        case DIRECTION_DOWN:
            //littleJump;
            break;
        case DIRECTION_LEFT:
        case DIRECTION_RIGHT:
            if(EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_PLAYER))
            {
                if (m_isShell && !m_isShellMoving)
                {
                    m_isShellMoving = true;
                    m_forwardDirection = -Vect2::forwardMulti(collDirection);
                    m_speed.setX((FORWARD_SPEED + KOOPA_SHELL_SPEED_BOOST) * m_forwardDirection);
                    m_rectangle->addX(m_forwardDirection*5.0f);
                }
            }
            else
            {
                goBack(collDirection);
                stop(collParams->static_.rect, collDirection);
                m_speed.setX((FORWARD_SPEED + KOOPA_SHELL_SPEED_BOOST * (int)m_isShell) * (int)m_isShellMoving * m_forwardDirection);
            }
            break;
        }
    }
}

Koopa::~Koopa()
{
}

