#ifndef NEWGRAPHICS_H_INCLUDED
#define NEWGRAPHICS_H_INCLUDED

#include "../common.h"
#include "renderDatas.h"
#include "gfxParameters.h"
#include "../gfxInterface.h"
#include "viewport.h"

namespace Graphics {

class Main
{
    public:
        Main();
        ~Main();

        inline void updateScreen() const {SDL_RenderPresent(m_gfxData->renderer);}

        void renderLevel();
        void renderMenu(Menu* menu);
        void renderEditor(Editor* editor);
        void renderButton(Button* button);

    private:
        inline void updateViewport() const {viewport->update();}

        GfxData* m_gfxData;
        RenderCoin* m_renderCoin;
        RenderDialog* m_renderDialog;
        RenderEntity* m_renderEntity;
        RenderBackground* m_renderBG;
        RenderEditor* m_renderEditor;

        SDL_Window* m_window;
};
}

#endif // NEWGRAPHICS_H_INCLUDED
