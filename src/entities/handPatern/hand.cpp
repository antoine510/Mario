#include "hand.h"
#include "gfxInterface.h"

HandPatternHand::HandPatternHand(int texID, int offsetX, int offsetY)
{
    m_gfxParameter = new GfxParameters();
    m_gfxParameter->init(&m_position, texID);
    m_offsetX = offsetX;
    m_offsetY = offsetY;
    gfxInterface->gfxStack.addStack(m_gfxParameter);
}

void HandPatternHand::updatePos(bool updateY, const Rectangle& pos, int length)
{
    if(updateY) {m_position.setY(pos.getY() - m_offsetY + length);}
    else        {m_position.setX(pos.getX() - m_offsetX + length);}
}

HandPatternHand::~HandPatternHand()
{
    gfxInterface->gfxStack.deleteStack(m_gfxParameter);
    delete m_gfxParameter;
}
