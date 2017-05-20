#ifndef PHYSTACK_H_INCLUDED
#define PHYSTACK_H_INCLUDED

#include "../common.h"
#include "../entities/entityTypes.h"
#include "sweepAndPrune.h"
#include "physics.h"

namespace Physic
{
    struct StaticParams
    {
        Rectangle* rect;
        int* type;
        Object* parent;
    };
    struct DynamicParams
    {
        Vect2* velocity;
        TYPE_TYPE* collisionMask;
    };
    struct CollisionParams
    {
        StaticParams static_;
        DynamicParams dynamic;
        Uint16 myClientID;
    };


    class Stack
    {
        public:
            int addStack(StaticParams staticParams, DynamicParams dynamicParams);
            int addStack(StaticParams staticParams);

            inline void deleteStatic(int pos) {m_sap.removeClient(m_staticsParams[pos].myClientID); m_staticsParams[pos].static_.rect = NULL;}
            inline void deleteDynamic(int pos) {m_sap.removeClient(m_dynamicsParams[pos].myClientID); m_dynamicsParams[pos].static_.rect = NULL;}

            void updateStack();
            void updateStackStatic();

            inline const std::vector<CollisionParams>& getStaticParams() const {return m_staticsParams;}
            inline const std::vector<CollisionParams>& getDynamicParams() const {return m_dynamicsParams;}
            inline CollisionParams& getStaticParam(int pos) {return m_staticsParams[pos];}
            inline CollisionParams& getDynamicParam(int pos) {return m_dynamicsParams[pos];}
            inline const std::vector< std::pair<SAPCandidate, SAPCandidate> >&  getCandidates() {return m_sap.getCandidates();}

        private:
            std::vector<CollisionParams> m_staticsParams;
            std::vector<CollisionParams> m_dynamicsParams;
            SweepAndPrune m_sap;
    };
    extern Stack* phyStack;
}

#endif // PHYSTACK_H_INCLUDED
