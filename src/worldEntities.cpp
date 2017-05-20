#include "worldEntities.h"
#include "physics/physics.h"
#include "physics/collisionHandler.h"
#include "entities/entitiesHeader.h"
#include "input.h"
#include <algorithm>

const std::unordered_map<std::string, EntityType> LevelEntities::entityTypeDecode = {
	{ "Player", ETYPE_PLAYER },
	{ "Goomba", ETYPE_GOOMBA },
	{ "Koopa", ETYPE_KOOPA },
	{ "Mushroom", ETYPE_MUSHROOM },
	{ "Ground", ETYPE_GROUND },
	{ "Decor", ETYPE_DECOR },
	{ "Brick", ETYPE_BRICK },
	{ "Switch", ETYPE_SWITCH },
	{ "HandPaternTrigger", ETYPE_TRIGGER_HP },
	{ "DialogTrigger", ETYPE_TRIGGER_DIALOG },
	{ "EndTrigger", ETYPE_TRIGGER_END },
};

LevelEntities::LevelEntities(xmlNodePtr level)
{
    entities = new EntitiesHandler();

	xmlNodePtr entityN = level->children;
	bypassText(entityN);
    while(entityN)
	{
        int x = asInt(entityN, "X"), y = asInt(entityN, "Y");

		std::string etypeName((const char*)entityN->name);
		auto search = entityTypeDecode.find(etypeName);
		SDL_assert(search != entityTypeDecode.end());
        switch(search->second)
        {
            case ETYPE_PLAYER:
                entities->addEntity(new Player(asString(entityN, "name"), new Rectangle(x, y, 16, 32), 0, asInt(entityN, "keySet")));
                break;
            case ETYPE_GOOMBA:
                entities->addEntity(new Goomba(new Rectangle(x, y, 16, 16), 1));
                break;
            case ETYPE_KOOPA:
                entities->addEntity(new Koopa(new Rectangle(x, y, 16, 24), 2));
                break;
            case ETYPE_MUSHROOM:
                entities->addEntity(new Mushroom(new Rectangle(x, y, 16, 16), 5, asInt(entityN, "itemType")));
                break;
            case ETYPE_GROUND:
                entities->addEntity(new Ground(new Rectangle(x, y, asInt(entityN, "W"), asInt(entityN, "H")), asInt(entityN, "texID")));
                break;
            case ETYPE_DECOR:
                entities->addEntity(new Decor(new Rectangle(x, y, asInt(entityN, "W"), asInt(entityN, "H")), asInt(entityN, "texID"), asInt(entityN, "layer")));
                break;
            case ETYPE_BRICK:
                entities->addEntity(new Brick(new Rectangle(x, y, 16, 16), 6));
                break;
            case ETYPE_SWITCH:
                entities->addEntity(new Switch(new Rectangle(x, y, 16, 16), 7));
                break;
            case ETYPE_TRIGGER_HP:
                entities->addEntity(new HPTrigger(new Rectangle(x, y, asInt(entityN, "W"), asInt(entityN, "H")), asString(entityN, "handPaternFile"), this));
                break;
            case ETYPE_TRIGGER_DIALOG:
                entities->addEntity(new DialogTrigger(new Rectangle(x, y, asInt(entityN, "W"), asInt(entityN, "H")), asString(entityN, "dialogFile")));
                break;
            case ETYPE_TRIGGER_END:
                entities->addEntity(new EndTrigger(new Rectangle(x, y, asInt(entityN, "W"), asInt(entityN, "H"))));
                break;
        }
		switchNextNode(entityN);
    }

    m_handPattern = NULL;
}

LevelEntities::~LevelEntities()
{
    if(m_handPattern != NULL) delete m_handPattern;
    delete entities;
}

void LevelEntities::updateAll(KeyStates* keystates, bool* gameover)
{
    if(m_handPattern != NULL) {if(m_handPattern->update()) {delete m_handPattern; m_handPattern = NULL;}}

    entities->updatePlayers(keystates, gameover);
    entities->updateType(TINDEX_ENEMY);
    entities->updateType(TINDEX_ITEM);
    entities->updateType(TINDEX_PROJECTILE);
    entities->updateType(TINDEX_BLOCK);
    entities->updateType(TINDEX_TRIGGER);
}

