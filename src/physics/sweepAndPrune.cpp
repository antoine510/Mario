#include "sweepAndPrune.h"
#include "phyStack.h"

using namespace Physic;

Physic::SweepAndPrune::SweepAndPrune()
{
    m_pointsSize = 0;
    for(SAP_CLIENTID i = 0; i < SAP_MAX_CLIENTS; i++) m_clients[i].phyStackPos = -1;
}

void Physic::SweepAndPrune::addClient(int phyStackPos, bool isDynamic, float xmin, float xmax)
{
    SAPClient t = {phyStackPos, SAP_POINTID(m_pointsSize), SAP_POINTID(m_pointsSize+1), isDynamic};
    for(SAP_CLIENTID i = 0; i < SAP_MAX_CLIENTS; i++)
    {
        if(m_clients[i].phyStackPos == -1)
        {
            m_clients[i] = t;
            if(isDynamic)
                phyStack->getDynamicParam(phyStackPos).myClientID = i;
            else
                phyStack->getStaticParam(phyStackPos).myClientID = i;

            SAPPoint tmin = {xmin, i, false}, tmax = {xmax, i, true};
            m_points[m_pointsSize] = tmin;
            m_points[m_pointsSize+1] = tmax;
            m_pointsSize += 2;

            break;
        }
    }
}

void Physic::SweepAndPrune::addCandidate(SAP_CLIENTID a, SAP_CLIENTID b)
{
    if(!m_clients[a].isDynamic && !m_clients[b].isDynamic) return;     //We are interested in static pairs
    SAPCandidate ca = {m_clients[a].phyStackPos, a, m_clients[a].isDynamic}, cb = {m_clients[b].phyStackPos, b, m_clients[b].isDynamic};
    m_candidates.emplace_back(ca, cb);
}

void Physic::SweepAndPrune::updateClient(SAP_CLIENTID clientID, float xmin, float xmax)
{
    m_points[m_clients[clientID].xminRef].value = xmin;
    m_points[m_clients[clientID].xmaxRef].value = xmax;
}

void Physic::SweepAndPrune::sortPoints()
{
    for(SAP_POINTID i = 1; i < m_pointsSize; i++)
    {
        for(SAP_POINTID k = i; k > 0 && (m_points[k].value < m_points[k-1].value); k--)
        {
            if(m_points[k].isMax && !m_points[k-1].isMax)                      //Adding or removing pairs if necessary
                removeCandidate(m_points[k].parent, m_points[k-1].parent);
            else if(!m_points[k].isMax && m_points[k-1].isMax)
                addCandidate(m_points[k].parent, m_points[k-1].parent);

            if(m_points[k].isMax)   m_clients[m_points[k].parent].xmaxRef--;   else m_clients[m_points[k].parent].xminRef--;    //Updating refs
            if(m_points[k-1].isMax) m_clients[m_points[k-1].parent].xmaxRef++; else m_clients[m_points[k-1].parent].xminRef++;

            SAPPoint t = m_points[k];           //Switching points
            m_points[k] = m_points[k-1];
            m_points[k-1] = t;
        }
    }
}

void Physic::SweepAndPrune::removeClient(SAP_CLIENTID clientID)
{
    removePoint(m_clients[clientID].xminRef);
    removePoint(m_clients[clientID].xmaxRef);

    removeCandidate(clientID);

    m_clients[clientID].phyStackPos = -1;
}

void Physic::SweepAndPrune::removePoint(SAP_POINTID id)
{
    for(SAP_POINTID i = id; i < m_pointsSize-1; i++)
    {
        m_points[i] = m_points[i+1];
        if(m_points[i].isMax)
            m_clients[m_points[i].parent].xmaxRef--;
        else
            m_clients[m_points[i].parent].xminRef--;
    }
    m_pointsSize--;
}

void Physic::SweepAndPrune::removeCandidate(SAP_CLIENTID a, SAP_CLIENTID b)
{
    if(!m_clients[a].isDynamic && !m_clients[b].isDynamic) return;     //We are interested in static pairs
    for(std::vector< std::pair<SAPCandidate, SAPCandidate> >::iterator it = m_candidates.begin(); it != m_candidates.end(); ++it)
    {
        if((it->first.id == a && it->second.id == b) || (it->first.id == b && it->second.id == a)) {
            m_candidates.erase(it);
            return;
        }
    }
}

void Physic::SweepAndPrune::removeCandidate(SAP_CLIENTID a)
{
	auto it = m_candidates.begin();
    while(it != m_candidates.end())
    {
        if(it->first.id == a || it->second.id == a) {
            it = m_candidates.erase(it);
			if (it == m_candidates.end()) return;
        }
		++it;
    }
}

