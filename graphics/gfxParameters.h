#ifndef GFXPARAMETERS_H_INCLUDED
#define GFXPARAMETERS_H_INCLUDED

#include "../common.h"
#include "../rectangle.h"
#include "../vector.h"
#include "textureSet.h"

#define POSITION_CENTER 0
#define POSITION_UP 1
#define POSITION_UPPERRIGHT 2
#define POSITION_RIGHT 3
#define POSITION_LOWERRIGHT 4
#define POSITION_DOWN 5
#define POSITION_LOWERLEFT 6
#define POSITION_LEFT 7
#define POSITION_UPPERLEFT 8

class GfxParameters
{
    public:
        void init(Rectangle* rect, int ID, int state = -1, int decorLayer = 0);
        void updateBlitPos();
        void updateState();
        void updateBlitRects();

        void blit();

        bool operator<(const GfxParameters& other) const;

        inline int getID() const {return m_texID;}
        inline int getState() const {return m_texState;}
        inline int getDecorLayer() const {return m_decorLayer;}
        inline std::vector< std::pair<Rectangle, int> >& getRects() {return m_blitRects;}
        inline bool isSet() const {return (m_texPtr != NULL);}
        inline Uint16 getMyGfxIndex() const {return m_myGfxIndex;}
        inline bool isOnStack() const {return m_onStack;}
        inline Uint8 getMyGfxLayer() const;

        inline void setState(int state) {m_texState = state;}
        inline void setDecorLayer(int layer) {m_decorLayer = layer;}
        void setMyTex(Graphics::TextureSet* myTex);
        inline void setMyGfxIndex(Uint16 index) {m_myGfxIndex = index;}
        inline void setIsOnStack(bool isOnStack) {m_onStack = isOnStack;}

    private:
        void computeSubRects(Rectangle* base, int texW, int texH, int state);
        void computeSubRects(int x, int y, int w, int h, int texW, int texH, int state);
        inline void addBlitRect(Rectangle rect, int state) {m_blitRects.push_back(std::pair<Rectangle,int>(rect, state));}
        inline void addBlitRectNatural(Rectangle rect, int state) {if(rect.isNatural()) addBlitRect(rect, state);}

        std::vector< std::pair<Rectangle, int> > m_blitRects;
        Rectangle* m_sourceRect;
        int m_texID;
        int m_texState;
        int m_decorLayer;
        Uint16 m_myGfxIndex;
        bool m_onStack;

        Graphics::TextureSet* m_texPtr;
};

#endif // GFXPARAMETERS_H_INCLUDED
