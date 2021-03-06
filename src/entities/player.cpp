#include "player.h"
#include <algorithm>
#include "../input.h"
#include "../timer.h"
#include "../sound.h"
#include "entitiesHandler.h"
#include "entitiesHeader.h"
#include "../physics/collisionHandler.h"
#include "../physics/physics.h"

Player::Player(std::string name, Rectangle* rectangle, int TexID, int keySet) : DynamicObject(rectangle, TexID), 
	m_name(name), 
	m_keySet(keySet),
	m_hurtTimer(new Timer(m_hurtTimerTime)),
	m_firingTimer(new Timer(m_firingTimerTime)),
	m_killTimer(new Timer(m_deathTimerTime)),
	m_flashTimer(new LoopingTimer(m_flashTimerTime))
{
    m_type = TINDEX_PLAYER;
    m_collideWith = (ENTMASK_S_AND_D | ENTMASK_TRIGGER) ^ ENTMASK_PLAYER;

    reshape();

    //Gfx data
    gfxInterface->setPlayer(m_rectangle->getXptr(), &m_coinNumber);
}

int Player::textureState()
{
    if (!m_isAlive) return 6;
    if (m_hurtTimer->isRunning() && (m_flashTimer->getLoopingCount() % 2)) return 17;
    if (m_isLeaning) return 7+m_direction+2*(m_life-1);
    if (m_speed.getY() > 0) return 102+m_direction+4*m_life;
    if (m_speed.getX() != 0 && m_liesOnFloor) return 100+m_direction+4*m_life;
    if (!m_liesOnFloor) return 11+m_direction+2*m_life;
    return m_direction+2*m_life;
}

void Player::jump(bool enableSound)
{
    m_speed.setY(m_jumpForce);
    if (enableSound) soundStack->addToStack(Sounds::JUMP);
}

void Player::addCoin(int amount)
{
    m_coinNumber += amount;
    //soundStack->addToStack(SOUND_COIN);
}

void Player::addLife()
{
	if (m_life < FIRE_MARIO) m_life = LifeLevel(m_life +1);
	reshape();
    soundStack->addToStack(Sounds::POWERUP);
}

bool Player::canStandUp()
{
    bool basePos;
    bool otherPos;
    float tempX = m_speed.getX();
    m_speed.setX(0.0f);
    m_speed.addY(-1.0f);
    m_rectangle->addY(-1.0f);

    Physic::setMyStaticColls(m_phyStackPos);
    m_CH->reset();
    basePos = m_CH->upAndDownTest();

    if(tempX < 0.0f) {m_rectangle->addX(1.0f);}
    else             {m_rectangle->addX(-1.0f);}
    Physic::setMyStaticColls(m_phyStackPos);
    m_CH->reset();
    otherPos = m_CH->upAndDownTest();

    if(tempX < 0.0f) {m_rectangle->addX(-1.0f);}
    else             {m_rectangle->addX(1.0f);}
    m_rectangle->addY(1.0f);
    m_speed.setX(tempX);
    m_speed.addY(1.0f);

    return !(basePos && otherPos);
}

void Player::update(KeyStates* keystates)
{
    if (!m_isAlive && !m_killTimer->isRunning()) destroy();

    m_isSpeeding = keystates->isSpeed();
    if (m_speed.getAbsX() <= (m_isSpeeding ? m_maxSideSpeed : m_maxSideSpeedSpeeding ))
    {
        if (keystates->isRight(m_keySet))
        {
            m_speed.integrate(m_isSpeeding ? m_sideAcceleration : m_sideAccelerationSpeeding, 0);
            m_direction = HDIRECTION_R;
        }
        else if (keystates->isLeft(m_keySet))
        {
            m_speed.integrate(m_isSpeeding ? -m_sideAcceleration : -m_sideAccelerationSpeeding, 0);
            m_direction = HDIRECTION_L;
        }
    }
    else    // Vitesse non reglementaire
    {
        m_speed.subAbsX(30/PS);
    }

    if(keystates->isFire(m_keySet) && m_life == FIRE_MARIO) fire();
    if(keystates->isHoldDelete())
        reshape();

    if (m_liesOnFloor)
    {
        if (keystates->isSpace(m_keySet) && !m_isLeaning) {jump(true);}

        /*If the player is not walking/runing we apply a constant deceleration*/
        if ((!keystates->isLeft(m_keySet) && !keystates->isRight(m_keySet)))
        {
            if (m_speed.getAbsX() > m_minSideSpeed) {m_speed.subAbsX(m_sideSpeedBrake);} else {m_speed.setX(0);}    /*Or we stop*/
        }
    }

    if(m_life != LITTLE_MARIO)
    {
        if(keystates->isDown(m_keySet)) {m_isLeaning = true; reshape();}
        else if(m_isLeaning) {
            m_isLeaning = false; reshape();                     //We try to stand up
            if(!canStandUp()) {m_isLeaning = true; reshape();}
        }
    }

    DynamicObject::update();
}

void Player::reshape()
{
    switch (m_life)
    {
        case LITTLE_MARIO:
            m_rectangle->setWH(12,16);
            m_isLeaning = false;
            break;
        case BIG_MARIO:
        case FIRE_MARIO:
            if (m_isLeaning) {m_rectangle->setWH(16,22);} else {m_rectangle->setWH(16,32);}
            break;
        default:
            m_rectangle->setWH(15, 14);
            break;
    }
    m_gfxParameters.setState(textureState());
    m_gfxParameters.updateBlitRects();
}

void Player::hurt()
{
    if (!m_hurtTimer->isRunning())
    {
        subLife();
        if(m_isAlive) soundStack->addToStack(Sounds::HURT);
        m_flashTimer->stop();
        m_flashTimer->start();
    }
    m_hurtTimer->start();
}

void Player::fire()
{
    if (!m_firingTimer->isRunning())
    {
        entities->addEntity(new Projectile(*m_rectangle, m_speed, m_direction));
        soundStack->addToStack(Sounds::FIREBALL);
    }
    m_firingTimer->start();
}

void Player::kill()
{
    if(entities->getEntityCount(TINDEX_PLAYER) > 1) {soundStack->addToStack(Sounds::PLAYERDEATH_LITE);}
    else {soundStack->stopMusic(); soundStack->addToStack(Sounds::PLAYERDEATH);}

    m_killTimer->start();
    DynamicObject::kill();
}

void Player::collide(const Physic::CollisionParams* collParams, int collDirection)
{
    if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_STATIC))
    {
        if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_BLOCK) && collDirection == DIRECTION_UP)
        {
            addCoin(1);
            collParams->static_.parent->destroy();
            soundStack->addToStack(Sounds::BREAK_BLOCK);
            stop(collParams->static_.rect, collDirection);
        }
        else if (*collParams->static_.type == TINDEX_TRIGGER) {
            ((HPTrigger*)(collParams->static_.parent))->activate();
            //if(((Trigger*)(collParams->static_.parent))->getTriggerType() == END);
        }
        else {stop(collParams->static_.rect, collDirection);}
    }
    else if (EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_MUSHROOM))
    {
        ((Mushroom*)collParams->static_.parent)->reward(this);
    }
    else
    {
        if(collDirection == DIRECTION_DOWN)
        {
            jump(false);
            addCoin(1);
            soundStack->addToStack(Sounds::STOMP_ENEMY);
        }
        else if(collDirection == DIRECTION_UP)
        {
            hurt();
        }
        else
        {
            if(EntitiesHandler::matchMasks(*collParams->static_.type, TINDEX_KOOPA))
            {
                if(((Koopa*)collParams->static_.parent)->isAggressive()) hurt();
            }
            else
            {
                hurt();
            }
        }
    }
}

Player::~Player()
{
    delete m_hurtTimer;
	delete m_firingTimer;
	delete m_killTimer;
	delete m_flashTimer;
}

