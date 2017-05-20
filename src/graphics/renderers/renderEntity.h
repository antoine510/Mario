#ifndef RENDERENTITY_H_INCLUDED
#define RENDERENTITY_H_INCLUDED

#include "../../common.h"
#include "../gfxParameters.h"

namespace Graphics{
class RenderEntity
{
    public:
        RenderEntity(GfxData* renderDatas);

        inline void render(GfxParameters* gfxParameters) {gfxParameters->blit();}

    protected:
        GfxData* m_gfxData;
};
}

#endif // RENDERENTITY_H_INCLUDED
