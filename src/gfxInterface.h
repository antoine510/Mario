#ifndef GFXINTERFACE_H_INCLUDED
#define GFXINTERFACE_H_INCLUDED

#include "common.h"

#include "graphics/gfxParameters.h"

struct PointerCompare
{
    bool operator()(const GfxParameters* l, const GfxParameters* r) {
        return *l < *r;
    }
};

class GfxStack
{
    public:
        void addStack(GfxParameters* element);
        void sortStack();
        void deleteStack(GfxParameters* element);
        inline const std::vector<GfxParameters*>& getElements() const {return m_stack;}

    private:
        std::vector<GfxParameters*> m_stack;
};

class GfxInterface
{
    public:
        GfxInterface();
        //Globals
        void setPlayer(float* playerXPos, int* playerCoins);

        float* playerXPosition;
        int* playerCoinAmount;
        int* backgroundID;

        //Stack
        GfxStack gfxStack;

    private:
        bool m_playerSet;
};
extern GfxInterface* gfxInterface;

#endif // GFXINTERFACE_H_INCLUDED
