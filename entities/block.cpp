#include "block.h"
#include "player.h"

Block::Block(Rectangle* rectangle, int TexID) : StaticObject(rectangle, TexID)
{
    m_type = TINDEX_BLOCK;
    Physic::StaticParams t = {m_rectangle, &m_type, this};
    m_phyStackPos = Physic::phyStack->addStack(t);
}

Block::~Block()
{
    Physic::phyStack->deleteStatic(m_phyStackPos);
}

Brick::Brick(Rectangle* rectangle, int TexID) : Block(rectangle, TexID)
{
    m_type = TINDEX_BRICK;
}

Brick::~Brick()
{

}

Switch::Switch(Rectangle* rectangle, int TexID) : Block(rectangle, TexID)
{
    m_type = TINDEX_SWITCH;
}

Switch::~Switch()
{

}

