#ifndef TEXTURESET_H_INCLUDED
#define TEXTURESET_H_INCLUDED

#include "common.h"
#include "texture.h"
#include "filetool.h"
#include "animation.h"
#include <unordered_map>

#define TEX_COIN 0

#define ANIMATION_OFFSET 100

namespace Graphics {

enum class TextureType : Uint8 { OBJECT, BUTTON, BACKGROUND, OTHER, COUNT };

class TextureSet {
public:
	TextureSet(Uint8 gfxLayer, bool composite, Uint8 defaultState);
	~TextureSet();

	void addState(unsigned int stateID, Texture* texture);
	void addAnim(unsigned int animID, Animation* anim);

	Texture* getState(unsigned int stateID);
	Texture* getDefault() { return getState(m_defaultState); }
	inline Uint8 getDefaultState() const { return m_defaultState; }
	inline Uint8 getGfxLayer() const { return m_gfxLayer; }
	inline bool isComposite() const { return m_composite; }

	inline void frameReset() { m_currentUser = 0; }

protected:
	std::vector<Texture*> m_texStates;
	std::vector<Animation*> m_texAnims;
	int m_currentAnim[Animation::maxUsers];
	int m_currentUser;
	bool m_animated;
	bool m_composite;
	Uint8 m_gfxLayer;
	Uint8 m_defaultState;
};

class TextureSetHandler {
public:
	TextureSetHandler(SDL_Renderer* renderer);
	~TextureSetHandler();

	void readTextureFile();
	void assignTextures(xmlNodePtr texGroup, TextureType type);

	void frameReset();

	inline Texture* getTex(TextureType type, int texID, int state) const { return m_textures[texID + m_offsets[(int)type]]->getState(state); }
	inline Texture* getDefault(TextureType type, int texID) const { return m_textures[texID + m_offsets[(int)type]]->getDefault(); }
	inline TextureSet* getTexSet(TextureType type, int texID) const { return m_textures[texID + m_offsets[(int)type]]; }

private:
	std::vector<TextureSet*> m_textures;
	unsigned int m_offsets[(int)TextureType::COUNT] = { 0 };
	SDL_Renderer* m_renderer;

	static const std::unordered_map<std::string, TextureType> stringToType;

	static const std::string texturePath;
};
}

#endif // TEXTURESET_H_INCLUDED
