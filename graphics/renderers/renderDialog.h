#ifndef RENDERDIALOG_H_INCLUDED
#define RENDERDIALOG_H_INCLUDED

#include "../../common.h"
#include "../renderDatas.h"

namespace Graphics{
class RenderDialog
{
    public:
        RenderDialog(GfxData* renderDatas);
        ~RenderDialog();

        void render();

    protected:
        GfxData* m_gfxData;

        Rectangle m_dialogTextPos;
        Rectangle m_dialogBoxPos;
        Texture* m_dialogTextTexture;

        bool m_dialogWasInactive;
};
}

#endif // RENDERDIALOG_H_INCLUDED
