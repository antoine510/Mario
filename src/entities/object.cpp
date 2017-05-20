#include "object.h"
#include "../physics/collisionHandler.h"
#include "../gfxInterface.h"

Object::Object(Rectangle* rectangle, int texID)
{
    m_rectangle = rectangle;
    m_hasToBeDeleted = false;

    m_gfxParameters.init(m_rectangle, texID);
    gfxInterface->gfxStack.addStack(&m_gfxParameters);
}

Object::~Object()
{
    gfxInterface->gfxStack.deleteStack(&m_gfxParameters);
    delete m_rectangle;
}

DynamicObject::DynamicObject(Rectangle* rectangle, int TexID) : Object(rectangle, TexID)
{
    m_isAlive = true;
    m_liesOnFloor = false;
    m_CH = new CollisionHandler(this);
    Physic::StaticParams t = {m_rectangle, &m_type, this};
    Physic::DynamicParams t2 = {&m_speed, &m_collideWith};
    m_phyStackPos = Physic::phyStack->addStack(t, t2);
}

void DynamicObject::update()
{
    if (m_isAlive)
    {
        if(m_speed.getY() > -MAX_DOWN_SPEED)
        {
            m_speed.integrate(0,-GRAVITY); /** We apply the Gravity acceleration (pixel/s²) until MAX_DOWN_SPEED is reached**/
        }
        m_rectangle->applySpeed(&m_speed);
        go();
    }
    if(m_rectangle->getOffsetH() < 0) {kill(); destroy();}
}

void DynamicObject::goBack(int collDirection)
{
    if (collDirection == DIRECTION_LEFT || collDirection == DIRECTION_RIGHT)
    {
        m_forwardDirection = -m_forwardDirection;
    }
}

void DynamicObject::kill()
{
    m_isAlive = false;
    m_collideWith = TINDEX_NOTHING;
}

void DynamicObject::stop(Rectangle* rect, int collDirection)
{
    switch(collDirection)
    {
        case DIRECTION_UP:
            m_speed.setY(0);
            m_rectangle->setY(rect->getFY() - m_rectangle->getFH());
            break;
        case DIRECTION_DOWN:
            m_speed.setY(0);
            m_rectangle->setY(rect->getOffsetFH());
            m_liesOnFloor = true;
            break;
        case DIRECTION_LEFT:
            m_speed.setX(0);
            m_rectangle->setX(rect->getOffsetFW());
            break;
        case DIRECTION_RIGHT:
            m_speed.setX(0);
            m_rectangle->setX(rect->getFX() - m_rectangle->getFW());
            break;
        default:
            break;
    }
}

DynamicObject::~DynamicObject()
{
    delete m_CH;
    Physic::phyStack->deleteDynamic(m_phyStackPos);
}

StaticObject::StaticObject(Rectangle* rectangle, int TexID) : Object(rectangle, TexID)
{
}

StaticObject::~StaticObject()
{
}

Ground::Ground(Rectangle* rectangle, int TexID) : StaticObject(rectangle, TexID)
{
    Physic::StaticParams t = {m_rectangle, &m_type, this};
    m_phyStackPos = Physic::phyStack->addStack(t);
    m_type = TINDEX_GROUND;
}

Ground::~Ground()
{
    Physic::phyStack->deleteStatic(m_phyStackPos);
}

Decor::Decor(Rectangle* rectangle, int TexID, int decorLayer) : Object(rectangle, TexID)
{
    m_type = TINDEX_DECOR;
    m_gfxParameters.setDecorLayer(decorLayer);
}

Decor::~Decor()
{
}
