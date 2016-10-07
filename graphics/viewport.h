#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED

#include "../common.h"
#include "../vector.h"
#include "../path.h"
#include "../timer.h"

#define VPMODE_COUNT 2
#define VP_SWITCH_TIME 390

namespace Graphics{
enum ViewPortMode {VPMODE_STATIC, VPMODE_PLAYER};

class ViewPort
{
    public:
        ViewPort(ViewPortMode mode = VPMODE_STATIC) : m_mode(mode), m_switchTimer(VP_SWITCH_TIME, false) {}

        void update();

        const Vect2 getOffset() {return (m_switchTimer.isRunning()) ? m_path.getValue(m_switchTimer.getEllapsedRatio()) : m_offset[m_mode];}

        void setMode(ViewPortMode mode);
        inline void setOffset(Vect2 offset) {m_offset[m_mode] = offset;}

    private:
        Vect2 m_offset[VPMODE_COUNT];
        ViewPortMode m_mode;
        Timer m_switchTimer;
        Path2D m_path;
};

extern ViewPort* viewport;
}

#endif // VIEWPORT_H_INCLUDED
