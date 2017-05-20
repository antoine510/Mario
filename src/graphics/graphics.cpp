#include "graphics.h"
#include "../menu.h"
#include "../ui/button.h"
#include "../ui/dialog.h"
#include "background.h"
#include "renderers/renderCoin.h"
#include "renderers/renderDialog.h"
#include "renderers/renderEntity.h"
#include "renderers/renderEditor.h"
#include "color.h"

using namespace Graphics;

/** Global Var **/
ViewPort* Graphics::viewport;

Main::Main()
{
    m_gfxData = new GfxData;
    gfxInterface = new GfxInterface;

    //if(SDL_SetHint("SDL_HINT_RENDER_DRIVER", "opengl") == SDL_TRUE) std::cout << "Using OpenGl\n";

    m_window = SDL_CreateWindow("Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0/*SDL_WINDOW_FULLSCREEN_DESKTOP*/);
    if(m_window) std::cout << "Created Window\n";

    m_gfxData->renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if(m_gfxData->renderer) std::cout << "Created Renderer\n";

    SDL_SetRenderDrawColor(m_gfxData->renderer, 0, 0, 0, 255);
    SDL_RenderSetLogicalSize(m_gfxData->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    m_gfxData->write = new Write(m_gfxData->renderer);
    std::cout << "Writing good\n\n";

    m_gfxData->textureSetHandler = new TextureSetHandler(m_gfxData->renderer);
    std::cout << "Texture Sets good\n\n";

    viewport = new ViewPort(VPMODE_PLAYER);

    m_renderCoin = new RenderCoin(m_gfxData);
    m_renderDialog = new RenderDialog(m_gfxData);
    m_renderEntity = new RenderEntity(m_gfxData);
    m_renderEditor = new RenderEditor(m_gfxData);

    m_renderBG = new RenderBackground(*m_gfxData);
    std::cout << "Backgrounds good\n\n";
}

void Main::renderLevel()
{
    updateViewport();
    m_renderBG->renderBG(BG_LEVEL);

    m_gfxData->textureSetHandler->frameReset();

    bool sortStack = false;
    const std::vector<GfxParameters*>& curStack = gfxInterface->gfxStack.getElements();
    for (std::vector<GfxParameters*>::const_iterator it = curStack.begin(); it != curStack.end(); ++it)
    {
        if(!(*it)->isSet()) {
            (*it)->setMyTex(m_gfxData->textureSetHandler->getTexSet(TextureType::OBJECT, (*it)->getID()));
            (*it)->updateBlitRects();
            sortStack = true;
        }
        m_renderEntity->render(*it);
    }
    if(sortStack) gfxInterface->gfxStack.sortStack();     //Sort stack by layer

    //m_renderCoin->render(*gfxInterface->playerCoinAmount);
    //m_renderCoin->render(Physic::phyStack->getCandidates().size());
    m_renderDialog->render();
}

void Main::renderMenu(Menu* menu)
{
    m_renderBG->renderBG(BG_MENU);

    m_gfxData->textureSetHandler->frameReset();
    for (std::vector<Button*>::iterator button = menu->m_buttons[menu->m_mode].begin(); button != menu->m_buttons[menu->m_mode].end();++button)
    {
        if((*button) != NULL) renderButton(*button);
    }
}

void Main::renderEditor(Editor* editor)
{
    renderLevel();

    m_renderEditor->render(editor);
}

void Main::renderButton(Button* button)
{
    if(!button->isValid()) {
        Texture* temp = m_gfxData->textureSetHandler->getTex(TextureType::BUTTON, button->m_texID, (int)button->m_state);
        button->getRect().setWH(temp->getW(), temp->getH());
        temp->blit(&button->m_rectangle);
    }
    else {
        m_gfxData->textureSetHandler->getTex(TextureType::BUTTON, button->m_texID, (int)button->m_state)->blit(&button->m_rectangle);
    }
}

Main::~Main()
{
    delete viewport;
    delete m_renderEditor;
    delete m_renderCoin;
    delete m_renderDialog;
    delete m_renderEntity;

    delete gfxInterface;
    delete m_gfxData->textureSetHandler;
    delete m_gfxData->write;

    SDL_DestroyRenderer(m_gfxData->renderer);
    SDL_DestroyWindow(m_window);

    delete m_gfxData;
}

