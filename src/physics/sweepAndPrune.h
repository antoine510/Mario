#ifndef SWEEPANDPRUNE_H_INCLUDED
#define SWEEPANDPRUNE_H_INCLUDED

#include "common.h"
#include <list>

#define SAP_CLIENTID Uint16
#define SAP_POINTID Uint16
#define SAP_MAX_CLIENTS 8191

namespace Physic
{
    struct SAPPoint {
        float value;
        SAP_CLIENTID parent;
        bool isMax;
    };
    struct SAPClient {
        int phyStackPos;
        SAP_POINTID xminRef;
        SAP_POINTID xmaxRef;
        bool isDynamic;
    };
    struct SAPCandidate {
        int phyStackPos;
        SAP_CLIENTID id;
        bool isDynamic;
    };
    struct SAPCandidatePair {
        SAPCandidate c1;
        SAPCandidate c2;
    };

    class SweepAndPrune
    {
        public:
            SweepAndPrune();

            void addClient(int phyStackPos, bool isDynamic, float xmin, float xmax);
            void addCandidate(SAP_CLIENTID a, SAP_CLIENTID b);
            void updateClient(SAP_CLIENTID clientID, float xmin, float xmax);
            void sortPoints();
            void removePoint(SAP_POINTID id);
            void removeClient(SAP_CLIENTID clientID);
            void removeCandidate(SAP_CLIENTID a, SAP_CLIENTID b);
            void removeCandidate(SAP_CLIENTID a);

            inline const std::vector< std::pair<SAPCandidate, SAPCandidate> >& getCandidates() const {return m_candidates;}

        private:
            SAPPoint m_points[SAP_MAX_CLIENTS*2];
            SAP_POINTID m_pointsSize;
            SAPClient m_clients[SAP_MAX_CLIENTS];
            std::vector< std::pair<SAPCandidate, SAPCandidate> > m_candidates;
    };
}

#endif // SWEEPANDPRUNE_H_INCLUDED
