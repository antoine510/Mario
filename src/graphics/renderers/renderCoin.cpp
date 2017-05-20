#include "renderCoin.h"
#include <sstream>

using namespace Graphics;

RenderCoin::RenderCoin(GfxData* renderDatas)
{
    m_gfxData = renderDatas;

    m_lastCoinAmount = -1;
    m_coinTextSurface = new Texture(m_gfxData->renderer);
    m_coinImgSurface = m_gfxData->textureSetHandler->getDefault(TextureType::OTHER, TEX_COIN);
    m_coinImgPosition = new Rectangle(50, 10, 0, 0, FRAME_SCREEN);
    m_coinTextPosition = new Rectangle(10, 10, 0, 0, FRAME_SCREEN);
}

void RenderCoin::render(int coinAmount)
{
    if (coinAmount != m_lastCoinAmount)
    {
        std::stringstream stream;
        stream << coinAmount;

        m_gfxData->write->write(stream.str(), m_coinTextSurface);

        m_coinTextPosition->setW(m_coinTextSurface->getW());
        m_coinTextPosition->setH(m_coinTextSurface->getH());
        m_coinImgPosition->setX(5 + m_coinTextPosition->getOffsetW());

        m_lastCoinAmount = coinAmount;
    }
    m_coinImgSurface->blit(m_coinImgPosition);
    m_coinTextSurface->blit(m_coinTextPosition);
}

RenderCoin::~RenderCoin()
{
    delete m_coinImgPosition;
    delete m_coinTextPosition;
    delete m_coinTextSurface;
}

