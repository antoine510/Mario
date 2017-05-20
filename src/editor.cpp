#include "editor.h"
#include "input.h"
#include "level.h"
#include "entities/entitiesHandler.h"
#include "entities/entitiesHeader.h"
#include "physics/phyStack.h"
#include "graphics/renderDatas.h"
#include "mathUtility.h"
#include "timer.h"

Editor::Editor(Level** level)
{
    m_currentLevel = level;
    m_moveHandle = NULL;
    m_creaHandle = NULL;
    m_viewHandle = false;
    m_selectedEntity = 0;
}

MarioMode Editor::update(KeyStates* keystates)
{
    int x, y, xS, yS;
    SDL_GetMouseState(&xS, &yS);
    y = SCREEN_HEIGHT + int(Graphics::viewport->getOffset().getY()) - yS -1;
    x = xS + int(Graphics::viewport->getOffset().getX());

    if(keystates->isHoldEditor())
    {
        Graphics::viewport->setMode(Graphics::VPMODE_PLAYER);
        timerStack->pauseTimers(false);
        return MODE_LEVEL;
    }
    if(keystates->isMouseLeftDown())
    {
        std::vector<Object*>& objects = entities->getObjects();
        for(unsigned int i = 0; i < objects.size(); i++)
        {
            Rectangle* rect = objects[i]->getObjectRectangle();
            if(rect->isInside(x, y))
            {
                m_moveEntityPos.setXY(x - rect->getX(), y - rect->getY());
                m_moveHandle = objects[i]; break;
            }
        }
    }
    else if(keystates->isMouseLeftUp())
    {
        Physic::phyStack->updateStackStatic();
        m_moveHandle = NULL;
    }
    else if(keystates->isMouseMiddleDown())
    {
        m_moveViewPos.setXY(x, y);
        m_viewHandle = true;
    }
    else if(keystates->isMouseMiddleUp()) {m_viewHandle = false;}
    else if(keystates->isMouseRightDown())
    {
        switch (m_selectedEntity)
        {
            case 0:
                entities->addEntity(new Goomba(new Rectangle(x, y, 16, 16), 1));
                break;
            case 1:
                entities->addEntity(new Koopa(new Rectangle(x, y, 16, 24), 2));
                break;
            case 2:
                entities->addEntity(new Mushroom(new Rectangle(x, y, 16, 16), 5));
                break;
            case 3:
                entities->addEntity(new Brick(new Rectangle(x, y, 16, 16), 6));
                break;
            case 4:
                m_creaHandle = new Ground(new Rectangle(x, y, 1, 1), 3);
                entities->addEntity(m_creaHandle);
                m_creatingPos.setXY(x, y);
                break;
        }
    }
    else if(keystates->isMouseRightUp())
    {
        Physic::phyStack->updateStackStatic();
        m_creaHandle = NULL;
    }
    else if(keystates->isHoldDelete())
    {
        std::vector<Object*>& objects = entities->getObjects();
        for(unsigned int i = 0; i < objects.size(); i++)
        {
            if(objects[i]->getObjectRectangle()->isInside(x, y))
            {
                entities->deleteEntity(objects[i]);
                break;
            }
        }
    }

    keystates->mouseWheelIncrement(&m_selectedEntity);
    clamp(&m_selectedEntity, 0, 9);

    if(m_moveHandle != NULL)
    {
        m_moveHandle->getObjectRectangle()->setXY(x - m_moveEntityPos.getX(), y - m_moveEntityPos.getY());
    }
    else if(m_creaHandle != NULL)
    {
        if(x < m_creatingPos.getX()) m_creaHandle->getObjectRectangle()->setX(x); else m_creaHandle->getObjectRectangle()->setX(m_creatingPos.getX());
        if(y < m_creatingPos.getY()) m_creaHandle->getObjectRectangle()->setY(y); else m_creaHandle->getObjectRectangle()->setY(m_creatingPos.getY());

        m_creaHandle->getObjectRectangle()->setWH(abs(x - m_creatingPos.getX()), abs(y - m_creatingPos.getY()));
        m_creaHandle->updateGfxParams();
    }
    else if(m_viewHandle)
    {
        Graphics::viewport->setOffset(Vect2(m_moveViewPos.getX() - x, m_moveViewPos.getY() - y) + Graphics::viewport->getOffset());
    }

    return MODE_EDITOR;
}

