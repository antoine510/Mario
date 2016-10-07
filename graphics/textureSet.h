#ifndef TEXTURESET_H_INCLUDED
#define TEXTURESET_H_INCLUDED

#include "../common.h"
#include "texture.h"
#include "../filetool.h"

#define TEX_COIN 0

#define ANIMATION_OFFSET 100
#define MAX_ANIMATION_USER 10

namespace Graphics{

enum TextureType {TEXTYPE_NONE = 0, TEXTYPE_OBJECT = 1, TEXTYPE_BUTTON = 2, TEXTYPE_BACKGROUND = 3, TEXTYPE_OTHER = 4};

class TextureSet
{
    public:
        TextureSet(Uint8 gfxLayer, bool composite, Uint8 defaultState);
        ~TextureSet();

        void addState(unsigned int stateID, Texture* texture);
        void addAnim(unsigned int animID, Animation* anim);

        Texture* getState(unsigned int stateID);
        Texture* getDefault() {return getState(m_defaultState);}
        inline Uint8 getDefaultState() const {return m_defaultState;}
        inline Uint8 getGfxLayer() const {return m_gfxLayer;}
        inline bool isComposite() const {return m_composite;}

        inline void frameReset() {m_currentUser = 0;}

    protected:
        std::vector<Texture*> m_texStates;
        std::vector<Animation*> m_texAnims;
        int m_currentAnim[MAX_ANIMATION_USER];
        int m_currentUser;
        bool m_animated;
        bool m_composite;
        Uint8 m_gfxLayer;
        Uint8 m_defaultState;
};

class TextureSetHandler
{
    public:
        TextureSetHandler(SDL_Renderer* renderer);
        ~TextureSetHandler();

        void readTextureFile();
        void assignTextures(xmlNodePtr texGroup);

        void frameReset();

        inline Texture* getTex(TextureType type, int texID, int state) const {return m_textures[texID + m_offsets[type-1]]->getState(state);}
        inline Texture* getDefault(TextureType type, int texID) const {return m_textures[texID + m_offsets[type-1]]->getDefault();}
        inline TextureSet* getTexSet(TextureType type, int texID) const {return m_textures[texID + m_offsets[type -1]];}

    private:
        std::vector<TextureSet*> m_textures;
        std::vector<unsigned int> m_offsets;
        SDL_Renderer* m_renderer;
};
}

#endif // TEXTURESET_H_INCLUDED
