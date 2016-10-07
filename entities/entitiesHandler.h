#ifndef ENTITIESHANDLER_H_INCLUDED
#define ENTITIESHANDLER_H_INCLUDED

#include "../common.h"
#include "entityTypes.h"
#include "../vector.h"

#define ENTBOXW 500
#define ENTBOXH 500

typedef struct
{
    std::vector<StaticObject*> statics;
} EntBox;

class EntitiesHandler
{
    public:
        EntitiesHandler();
        ~EntitiesHandler();

        void addEntity(Object* entity);
        void deleteEntity(Object* entity);

        void updatePlayers(KeyStates* keystates, bool* gameover);
        void updateType(int tIndex);
        void updateGfxData();

        inline std::vector<Object*>& getObjects() {return *(m_objects[TINDEX_ALL]);}
        inline std::vector<Object*>& getObjectsOfType(int entType) {return *(m_objects[entType]);}
        inline int getEntityCount(int entType) {return m_objects[entType]->size();}

        static TYPE_TYPE tMasks[TYPE_TINDEXCOUNT];
        static inline bool matchMasks(int entType1, int entType2) {return (tMasks[entType1] & tMasks[entType2]) != 0;}
        static inline bool matchMasks(int entType1, TYPE_TYPE type2) {return (tMasks[entType1] & type2) != 0;}

    private:
        void initTypeMasks();

        std::vector<Object*>* m_objects[TYPE_TINDEXCOUNT];
};

extern EntitiesHandler* entities;

#endif // ENTITIESHANDLER_H_INCLUDED
