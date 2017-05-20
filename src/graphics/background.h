#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "../common.h"
#include "renderDatas.h"

namespace Graphics {
class Background
{
    public:
        Background(int texID, int spanWidth, int spanSpeed);

        void refresh();

        inline int getTexID() const {return m_texID;}
        inline Rectangle* getRect() {return &m_drawingPos;}

    private:
        Rectangle m_drawingPos;
        int m_spanWidth;
        int m_spanSpeed;
        int m_texID;
};

enum BackgroundID {BG_MENU , BG_LEVEL};

class RenderBackground
{
    public:
        RenderBackground(const GfxData& gfxData);
        ~RenderBackground();

        void renderBG(BackgroundID id);

    private:
        const GfxData& m_gfxData;
        std::vector<Background> m_bgs;
};
}

#endif // BACKGROUND_H_INCLUDED
