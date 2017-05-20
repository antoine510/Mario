#ifndef WORLDENTITIES_H_INCLUDED
#define WORLDENTITIES_H_INCLUDED

#include <unordered_map>

#include "common.h"
#include "filetool.h"
#include "entities/entitiesHandler.h"
#include "entities/handPatern/handPattern.h"

enum EntityType {
	ETYPE_PLAYER,
	ETYPE_GOOMBA,
	ETYPE_KOOPA,
	ETYPE_MUSHROOM,
	ETYPE_GROUND,
	ETYPE_DECOR,
	ETYPE_BRICK,
	ETYPE_SWITCH,
	ETYPE_TRIGGER_HP,
	ETYPE_TRIGGER_DIALOG,
	ETYPE_TRIGGER_END
};

class LevelEntities
{
    public:
        LevelEntities(xmlNodePtr level);
        ~LevelEntities();

        inline std::vector<Object*>& getObjects() {return entities->getObjects();}
        inline std::vector<Object*>& getObjectsOfType(int entType) {return entities->getObjectsOfType(entType);}
        inline void setHandPatern(std::string hpName) {if(m_handPattern != NULL) delete m_handPattern; m_handPattern = new HandPattern(hpName);}

        void updateAll(KeyStates* keystates, bool* gameover);
        inline void updateGfxData() {entities->updateGfxData();}

    private:
		static const std::unordered_map<std::string, EntityType> entityTypeDecode;

        ///Entities* m_entities; GLOBAL
        HandPattern* m_handPattern;
};

#endif // WORLDENTITIES_H_INCLUDED
