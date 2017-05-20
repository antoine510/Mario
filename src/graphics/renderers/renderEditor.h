#ifndef RENDEREDITOR_H_INCLUDED
#define RENDEREDITOR_H_INCLUDED

#include "../../common.h"
#include "../renderDatas.h"
#include "../../rectangle.h"
#include "../gfxParameters.h"

namespace Graphics{
class RenderEditor
{
    public:
        RenderEditor(GfxData* renderDatas);
        ~RenderEditor();

        void render(Editor* editor);

    protected:
        GfxData* m_gfxData;

        Texture* m_backDrop;
        Rectangle m_backDropRect;

        Texture* m_selection;
        Rectangle m_selectionRect;

        Rectangle m_groundRect;
        GfxParameters m_groundParams;
};
}

#endif // RENDEREDITOR_H_INCLUDED
