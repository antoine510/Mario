#include "gfxParameters.h"
#include <algorithm>
#include "renderDatas.h"
#include "viewport.h"

void GfxParameters::init(Rectangle* rect, int ID, int state, int decorLayer)
{
    m_texID = ID;
    m_texState = state;
    m_decorLayer = decorLayer;
    m_onStack = false;

    m_texPtr = NULL;

    m_sourceRect = rect;
}

Uint8 GfxParameters::getMyGfxLayer() const
{
    if(m_texPtr == NULL) return 0;      //We haven't had time to be initialized by passing trough the graphics pipeline
    return m_texPtr->getGfxLayer();
}

void GfxParameters::setMyTex(Graphics::TextureSet* myTex)
{
    m_texPtr = myTex;
    if(m_texState == -1) m_texState = myTex->getDefaultState();
    if(!m_sourceRect->isNatural() && !myTex->isComposite())
        m_sourceRect->setWH(myTex->getState(m_texState)->getW(), myTex->getState(m_texState)->getH());
}

bool GfxParameters::operator<(const GfxParameters& other) const
{
    return (getMyGfxLayer() < other.getMyGfxLayer()) || (getMyGfxLayer() == other.getMyGfxLayer() && m_decorLayer > other.getDecorLayer());
}

void GfxParameters::blit()
{
    updateBlitPos();
    if(m_decorLayer == 0) {
        if(m_texPtr->isComposite()) {
            for (std::vector< std::pair<Rectangle, int> >::iterator it = m_blitRects.begin(); it != m_blitRects.end(); ++it)
            {
                m_texPtr->getState(it->second)->blit(&it->first);
            }
        }
        else {
            Graphics::Texture* tex = m_texPtr->getState(m_texState);
            for (std::vector< std::pair<Rectangle, int> >::iterator it = m_blitRects.begin(); it != m_blitRects.end(); ++it)
            {
                tex->blit(&it->first);
            }
        }
    }
    else
    {
        int layerOffset = (int)(0.25*(m_decorLayer*Graphics::viewport->getOffset().getX()));

        for (std::vector< std::pair<Rectangle, int> >::iterator it = m_blitRects.begin(); it != m_blitRects.end(); ++it)
        {
            it->first.addX(layerOffset);
            m_texPtr->getState(it->second)->blit(&it->first);
            it->first.addX(-layerOffset);
        }
    }
}

void GfxParameters::updateBlitPos()
{
    float deltaX = m_sourceRect->getFX() - m_blitRects[0].first.getFX();
    float deltaY = m_sourceRect->getFY() - m_blitRects[0].first.getFY();
    for (unsigned int i = 0; i < m_blitRects.size(); i++)
    {
        m_blitRects[i].first.addX(deltaX);
        m_blitRects[i].first.addY(deltaY);
    }
}

void GfxParameters::updateBlitRects()
{
    if(m_texPtr != NULL)
    {
        m_blitRects.clear();
        if(m_texPtr->isComposite())
        {
            int x = m_sourceRect->getX(), y = m_sourceRect->getY();
            int w = m_sourceRect->getW(), h = m_sourceRect->getH();
            int centerW = m_texPtr->getState(POSITION_CENTER)->getW();
            int centerH = m_texPtr->getState(POSITION_CENTER)->getH();
            int borderW = m_texPtr->getState(POSITION_UPPERRIGHT)->getW();
            int borderH = m_texPtr->getState(POSITION_UPPERRIGHT)->getH();

            addBlitRect(Rectangle(x          , y          , borderW, borderH), POSITION_LOWERLEFT); //x,y first for delta pos calculus
            computeSubRects(x+borderW  , y+borderH  , w-2*borderW, h-2*borderH, centerW, centerH, POSITION_CENTER);
            computeSubRects(x+borderW  , y+h-borderH, w-2*borderW, borderH    , centerW, borderH, POSITION_UP);
            computeSubRects(x+w-borderW, y+borderH  , borderW    , h-2*borderH, borderW, centerH, POSITION_RIGHT);
            computeSubRects(x+borderW  , y          , w-2*borderW, borderH    , centerW, borderH, POSITION_DOWN);
            computeSubRects(x          , y+borderH  , borderW    , h-2*borderH, borderW, centerH, POSITION_LEFT);
            addBlitRectNatural(Rectangle(x+w-borderW, y+h-borderH, borderW, borderH), POSITION_UPPERRIGHT);
            addBlitRectNatural(Rectangle(x+w-borderW, y          , borderW, borderH), POSITION_LOWERRIGHT);
            addBlitRectNatural(Rectangle(x          , y+h-borderH, borderW, borderH), POSITION_UPPERLEFT);
        }
        else
        {
            addBlitRect(*m_sourceRect, m_texState);
        }
    }
}

void GfxParameters::computeSubRects(int x, int y, int w, int h, int texW, int texH, int state)
{
    //if(w <= 0 or h <= 0) return;
    unsigned int loopsW = (w-1) / texW +1, loopsH = (h-1) / texH +1;
    int offsetW = x+w, offsetH = y+h;
    int saveY = y;

    for (unsigned int i = 0; i < loopsW; i++)
    {
        w = std::min(texW, offsetW - x);
        for (unsigned int j = 0; j < loopsH; j++)
        {
            h = std::min(texH, offsetH - y);
            addBlitRectNatural(Rectangle(x, y, w, h), state);
            y += h;
        }
        y = saveY;
        x += w;
    }
}

void GfxParameters::computeSubRects(Rectangle* base, int texW, int texH, int state)
{
    computeSubRects(base->getX(), base->getY(), base->getW(), base->getH(), texW, texH, state);
}

