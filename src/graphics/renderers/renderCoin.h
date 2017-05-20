#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "../../common.h"
#include "../surface.h"
#include "../renderDatas.h"

namespace Graphics{
class RenderCoin
{
    public:
        RenderCoin(GfxData* renderDatas);
        ~RenderCoin();

        void render(int coinAmount);

    protected:
        GfxData* m_gfxData;

        Rectangle* m_coinTextPosition;
        Rectangle* m_coinImgPosition;
        Texture* m_coinTextSurface;
        Texture* m_coinImgSurface;
        int m_lastCoinAmount;
};
}

#endif // COIN_H_INCLUDED
