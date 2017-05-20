#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED

#include "common.h"

#include "rectangle.h"
#include "graphics/gfxParameters.h"

class HandPatternHand
{
    public:
        HandPatternHand(int texID, int offsetX, int offsetY);
        ~HandPatternHand();

        void updatePos(bool updateY, const Rectangle& pos, int length);   //length is the value to add to the coordinate
        inline void updatePos(int x, int y) {m_position.setX(x - m_offsetX); m_position.setY(y - m_offsetY);}
        inline void updatePos(Vect2 pos) {updatePos(int(pos.getX()), int(pos.getY()));}

    private:
        Rectangle m_position;
        GfxParameters* m_gfxParameter;
        int m_offsetX;
        int m_offsetY;
};

#endif // HAND_H_INCLUDED
