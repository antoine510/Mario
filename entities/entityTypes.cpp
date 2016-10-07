#include "entityTypes.h"
#include "entitiesHandler.h"

TYPE_TYPE EntitiesHandler::tMasks[TYPE_TINDEXCOUNT];

void EntitiesHandler::initTypeMasks()
{
    tMasks[TINDEX_PLAYER] = 0x0001;
    tMasks[TINDEX_GOOMBA] = 0x0002;
    tMasks[TINDEX_KOOPA] = 0x0004;
    tMasks[TINDEX_MUSHROOM] = 0x0008;
    tMasks[TINDEX_PROJECTILE] = 0x0100;
    tMasks[TINDEX_DECOR] = 0x0010;
    tMasks[TINDEX_GROUND] = 0x0020;
    tMasks[TINDEX_BRICK] = 0x0040;
    tMasks[TINDEX_SWITCH] = 0x0080;
    tMasks[TINDEX_BLOCK] = 0x00C0;
    tMasks[TINDEX_TRIGGER] = 0x0200;
    tMasks[TINDEX_STATIC] = 0x02E0;
    tMasks[TINDEX_ITEM] = 0x0008;
    tMasks[TINDEX_ENEMY] = 0x0006;
    tMasks[TINDEX_DYNAMIC] = 0x010F;
    tMasks[TINDEX_ALL] = 0xFFFF;
    tMasks[TINDEX_NOTHING] = 0x0;
}

