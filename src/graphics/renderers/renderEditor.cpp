#include "renderEditor.h"
#include "../surface.h"
#include "../../editor.h"
#include "../../gfxInterface.h"

using namespace Graphics;

RenderEditor::RenderEditor(GfxData* renderDatas)
{
    m_gfxData = renderDatas;

    Surface t(SCREEN_WIDTH, SCREEN_HEIGHT/10);
    t.fillColor(Color(0, 0, 0, 64));
    m_backDrop = new Texture(m_gfxData->renderer, &t);
    m_backDropRect = Rectangle(0, 0, 0, 0, FRAME_SCREEN);

    Surface t2(SCREEN_WIDTH/10, SCREEN_HEIGHT/10);
    t2.fillColor(Color(0, 0, 255, 128));
    m_selection = new Texture(m_gfxData->renderer, &t2);
    m_selectionRect = Rectangle(0, 0, 0, 0, FRAME_SCREEN);

    m_groundRect = Rectangle(9*SCREEN_WIDTH/20-20, SCREEN_HEIGHT/20-20, 40, 40, FRAME_SCREEN);
    m_groundParams.init(&m_groundRect, 3);
    m_groundParams.setMyTex(m_gfxData->textureSetHandler->getTexSet(TextureType::OBJECT, 3));
    m_groundParams.updateBlitRects();
}

void RenderEditor::render(Editor* editor)
{
    m_backDrop->blit(&m_backDropRect);
    m_selectionRect.setX(editor->m_selectedEntity * SCREEN_WIDTH/10);
    m_selection->blit(&m_selectionRect);
    Rectangle entityRect(SCREEN_WIDTH/20, SCREEN_HEIGHT/20, 0, 0, FRAME_SCREEN);
    m_gfxData->textureSetHandler->getDefault(TextureType::OBJECT, 1)->blitCentered(entityRect);
    entityRect.addX(SCREEN_WIDTH/10);
    m_gfxData->textureSetHandler->getDefault(TextureType::OBJECT, 2)->blitCentered(entityRect);
    entityRect.addX(SCREEN_WIDTH/10);
    m_gfxData->textureSetHandler->getDefault(TextureType::OBJECT, 5)->blitCentered(entityRect);
    entityRect.addX(SCREEN_WIDTH/10);
    m_gfxData->textureSetHandler->getDefault(TextureType::OBJECT, 6)->blitCentered(entityRect);
    m_groundRect.toFramePhysics();
    m_groundParams.blit();
    m_groundRect.toFrameScreen();
}

RenderEditor::~RenderEditor()
{
    delete m_backDrop;
}

