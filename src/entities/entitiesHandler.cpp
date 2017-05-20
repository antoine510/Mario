#include "entitiesHandler.h"
#include "player.h"
#include "object.h"
#include "../input.h"

EntitiesHandler* entities;

EntitiesHandler::EntitiesHandler()
{
    initTypeMasks();

    for (unsigned int i = 0; i < TYPE_TINDEXCOUNT; i++)
    {
        m_objects[i] = new std::vector<Object*>;
    }
}

void EntitiesHandler::addEntity(Object* entity)
{
    int entType = entity->getType();
    int i;

    for (i = 0; i < TYPE_TINDEXCOUNT; i++)
    {
        if (matchMasks(entType, i))
        {
            m_objects[i]->push_back(entity);
        }
    }
}

void EntitiesHandler::deleteEntity(Object* entity)
{
    TYPE_TYPE entType = entity->getType();
    int i;

    for (i = 0; i < TYPE_TINDEXCOUNT; i++)
    {
        if (matchMasks(entType, i))
        {
            for (std::vector<Object*>::iterator obj = m_objects[i]->begin(); obj != m_objects[i]->end(); ++obj)
            {
                if(*obj==entity)
                {
                    m_objects[i]->erase(obj);
                    break;
                }
            }
        }
    }
    delete entity;
}

void EntitiesHandler::updatePlayers(KeyStates* keystates, bool* gameover)
{
    for (unsigned int i = 0; i != m_objects[TINDEX_PLAYER]->size(); i++)
    {
        ((Player*)((*m_objects[TINDEX_PLAYER])[i]))->update(keystates);
        if ((*m_objects[TINDEX_PLAYER])[i]->hasToBeDeleted())
        {
            deleteEntity((*m_objects[TINDEX_PLAYER])[i]);
            i--;
        }
    }
    (*gameover) = (m_objects[TINDEX_PLAYER]->size() == 0);
}

void EntitiesHandler::updateType(int tIndex)
{
    for (std::vector<Object*>::iterator it = m_objects[tIndex]->begin(); it != m_objects[tIndex]->end(); ++it)
    {
		Object* obj = *it;
        if (obj->hasToBeDeleted())
        {
			it = m_objects[tIndex]->erase(it);
            deleteEntity(obj);
			if (it == m_objects[tIndex]->end()) break;
        }
        else if (matchMasks(tIndex, TINDEX_DYNAMIC))
        {
            ((DynamicObject*)obj)->update();
        }
    }
}

void EntitiesHandler::updateGfxData()
{
    for (std::vector<Object*>::iterator obj = m_objects[TINDEX_ALL]->begin(); obj != m_objects[TINDEX_ALL]->end(); ++obj)
    {
        (*obj)->updateGfxData();
    }
}

EntitiesHandler::~EntitiesHandler()
{
    for (std::vector<Object*>::iterator obj = m_objects[TINDEX_ALL]->begin(); obj != m_objects[TINDEX_ALL]->end(); ++obj)
    {
        delete (*obj);
    }

    for (unsigned int i = 0; i < TYPE_TINDEXCOUNT; i++)
    {
        delete m_objects[i];
    }
}

