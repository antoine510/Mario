#include "gfxInterface.h"
#include <algorithm>

/** Global Var **/
GfxInterface* gfxInterface;

void GfxStack::addStack(GfxParameters* element)
{
    if(element->isOnStack()) return;
    m_stack.push_back(element);
    element->setMyGfxIndex(Uint16(m_stack.size()-1));
    element->setIsOnStack(true);
}

void GfxStack::sortStack()
{
    std::sort(m_stack.begin(), m_stack.end(), PointerCompare());                    //Sort by gfxLayer
    for(unsigned int i = 0; i < m_stack.size(); i++) m_stack[i]->setMyGfxIndex(i);  //Reset gfxIndexes
}

void GfxStack::deleteStack(GfxParameters* element)
{
    if(!element->isOnStack()) return;
    if(element->getMyGfxIndex() >= m_stack.size())
        std::cerr << "Error : tried to delete stack at position " << element->getMyGfxIndex() << " which is out of bound\n";
    m_stack.erase(m_stack.begin() + element->getMyGfxIndex());
    element->setIsOnStack(false);
    sortStack();
}

GfxInterface::GfxInterface()
{
    m_playerSet = false;
}

void GfxInterface::setPlayer(float* playerXPos, int* playerCoins)
{
    if(!m_playerSet) {
        playerXPosition = playerXPos;
        playerCoinAmount = playerCoins;
        m_playerSet = true;
    }
}
