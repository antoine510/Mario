#include "phyStack.h"
#include "../entities/object.h"

using namespace Physic;

/** Global Var **/
Stack* Physic::phyStack;

int Physic::Stack::addStack(StaticParams staticParams, DynamicParams dynamicParams)
{
    CollisionParams t = {staticParams, dynamicParams};
    bool done = false;
    int resu;
    for(unsigned int i = 0; i < m_dynamicsParams.size(); i++)
    {
        if(m_dynamicsParams[i].static_.rect == NULL)
        {
            m_dynamicsParams[i] = t;
            resu = i;
            done = true;
            break;
        }
    }
    if(!done) {
        m_dynamicsParams.push_back(t);
        resu = m_dynamicsParams.size()-1;
    }
    m_sap.addClient(resu, true, staticParams.rect->getFX(), staticParams.rect->getOffsetFW());
    return resu;
}

int Physic::Stack::addStack(StaticParams staticParams)
{
    CollisionParams t = {staticParams, {}};
    bool done = false;
    int resu;
    for(unsigned int i = 0; i < m_staticsParams.size(); i++)
    {
        if(m_staticsParams[i].static_.rect == NULL)
        {
            m_staticsParams[i] = t;
            resu = i;
            done = true;
            break;
        }
    }
    if(!done) {
        m_staticsParams.push_back(t);
        resu = m_staticsParams.size()-1;
    }
    m_sap.addClient(resu, false, staticParams.rect->getFX(), staticParams.rect->getOffsetFW());
    return resu;
}

void Physic::Stack::updateStack()
{
    for(unsigned int i = 0; i < m_dynamicsParams.size(); i++)
    {
        if(m_dynamicsParams[i].static_.rect != NULL)
        {
            m_sap.updateClient(m_dynamicsParams[i].myClientID, m_dynamicsParams[i].static_.rect->getFX(), m_dynamicsParams[i].static_.rect->getOffsetFW());
        }
    }
    m_sap.sortPoints();
}

void Physic::Stack::updateStackStatic()
{
    for(unsigned int i = 0; i < m_staticsParams.size(); i++)
    {
        if(m_staticsParams[i].static_.rect != NULL)
        {
            m_sap.updateClient(m_staticsParams[i].myClientID, m_staticsParams[i].static_.rect->getFX(), m_staticsParams[i].static_.rect->getOffsetFW());
        }
    }
    updateStack();
}

