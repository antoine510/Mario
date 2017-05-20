#include "viewport.h"
#include <algorithm>
#include "../gfxInterface.h"
#include "renderDatas.h"

using namespace Graphics;

void ViewPort::setMode(ViewPortMode mode)
{
    if(m_mode != mode)
    {
        if(m_switchTimer.isRunning())
        {
            Vect2 start = m_path.getValue(m_switchTimer.getEllapsedRatio());
            m_switchTimer.setDelay(m_switchTimer.getEllapsed());
            m_switchTimer.restart();
            m_path = Path2D(AMORTIZED, start, m_offset[mode] - start);
        }
        else
        {
            m_switchTimer.setDelay(VP_SWITCH_TIME);
            m_switchTimer.start();
            m_path = Path2D(AMORTIZED, m_offset[m_mode], m_offset[mode] - m_offset[m_mode]);
        }
    }
    m_mode = mode;
}

void ViewPort::update()
{
    switch(m_mode)
    {
        case VPMODE_STATIC:
            if(m_switchTimer.isRunning()) m_path.setDest(m_offset[VPMODE_STATIC]);
            break;
        case VPMODE_PLAYER:
            int camPos = std::max((int)(*gfxInterface->playerXPosition) - SCREEN_WIDTH / 2, 0);
            if(m_switchTimer.isRunning()) m_path.getXPath().setDest(float(camPos));
            m_offset[VPMODE_PLAYER].setXY(camPos, 0);
            break;
    }
}

