#include "renderDialog.h"
#include "../../ui/dialog.h"

using namespace Graphics;

RenderDialog::RenderDialog(GfxData* renderDatas)
{
    m_gfxData = renderDatas;

    m_dialogTextTexture = NULL;
    m_dialogBoxPos = Rectangle(25, 375, 0, 0, FRAME_SCREEN);
    m_dialogTextPos = Rectangle(40, 425, 0, 0, FRAME_SCREEN);
    m_dialogWasInactive = true;
}

void RenderDialog::render()
{
    if(dialog != NULL)
    {
        if(m_dialogWasInactive)
        {
            Texture* temp = m_gfxData->textureSetHandler->getDefault(TEXTYPE_OTHER, dialog->getTexID());    //Update dialogBox WH to compute text pos
            m_dialogBoxPos.setWH(temp->getW(), temp->getH());

            if(m_dialogTextTexture != NULL) delete m_dialogTextTexture;
            m_dialogTextTexture = new Texture(m_gfxData->renderer);

            m_gfxData->write->write(dialog->m_text, m_dialogTextTexture);

            m_dialogTextPos.setX((SCREEN_WIDTH - m_dialogTextTexture->getW()) / 2);
            m_dialogTextPos.setY(m_dialogBoxPos.getY() + m_dialogBoxPos.getH()/2 - m_dialogTextTexture->getH()/2);
        }

        m_gfxData->textureSetHandler->getDefault(TEXTYPE_OTHER, dialog->getTexID())->blit(&m_dialogBoxPos);
        if(m_dialogTextTexture != NULL) {m_dialogTextTexture->blit(&m_dialogTextPos);}

        m_dialogWasInactive = false;
    }
    else {m_dialogWasInactive = true;}
}

RenderDialog::~RenderDialog()
{
    delete m_dialogTextTexture;         //Deleting NULL is ok (it will be the case if we never render new text)
}

