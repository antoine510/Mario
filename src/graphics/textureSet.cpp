#include "textureSet.h"
#include <algorithm>
#include "animation.h"

using namespace Graphics;

const std::string TextureSetHandler::texturePath = "textures/";

const std::unordered_map<std::string, TextureType> TextureSetHandler::stringToType = {
	{ "texSets",		TextureType::OBJECT },
	{ "buttons",		TextureType::BUTTON },
	{ "backgrounds",	TextureType::BACKGROUND },
	{ "other",			TextureType::OTHER },
};

TextureSetHandler::TextureSetHandler(SDL_Renderer* renderer) : m_renderer(renderer) {
	readTextureFile();
}

void TextureSetHandler::readTextureFile() {
	std::cout << "Reading texture sets\n";

	xmlDocPtr textureDoc = parseXML(texturePath + "textures.xml");
	xmlNodePtr texGroups = xmlDocGetRootElement(textureDoc)->xmlChildrenNode;
	bypassText(texGroups);

	while(texGroups) {
		std::cout << "Assigning texture sets\n";
		assignTextures(texGroups, stringToType.at(getNodeName(texGroups)));
		switchNextNode(texGroups);
	}

	xmlFreeDoc(textureDoc);
}

void TextureSetHandler::assignTextures(xmlNodePtr texGroup, TextureType type) {
	xmlNodePtr texSetN = texGroup->children;
	bypassText(texSetN);

	TextureSet* currentTex;
	unsigned int currentTexID;
	unsigned int maxTexID = 0;
	std::string texsetRootPath = texturePath + asString(texGroup, "prefix");

	while(texSetN) {
		xmlNodePtr texElementN = texSetN->children;
		bypassText(texElementN);

		if(checkName(texSetN, "compositeSet"))
			currentTex = new TextureSet(asInt(texSetN, "gfxLayer"), true, 0);
		else
			currentTex = new TextureSet(asInt(texSetN, "gfxLayer"), false, asInt(texSetN, "defaultState"));
		currentTexID = asInt(texSetN, "id") + m_offsets[(int)type];

		while(texElementN) {
			std::string path = texsetRootPath + asString(texElementN, "path");

			if(checkName(texElementN, "state")) {
				currentTex->addState(asInt(texElementN, "id"), new Texture(m_renderer, path));
			} else {
				Animation* anim;
				if(asBool(texElementN, "loop")) {
					anim = new Animation(m_renderer, path, asInt(texElementN, "frameWidth"), asInt(texElementN, "frameCount"), asInt(texElementN, "delay"));
				} else {
					std::string fallbackPath = texsetRootPath + asString(texElementN, "fallback");
					anim = new NLAnimation(m_renderer, path, asInt(texElementN, "frameWidth"), asInt(texElementN, "frameCount"), asInt(texElementN, "delay"), fallbackPath);
				}
				currentTex->addAnim(asInt(texElementN, "id"), anim);
			}
			switchNextNode(texElementN);
		}

		if(m_textures.size() <= currentTexID) m_textures.resize(currentTexID + 1);
		m_textures[currentTexID] = currentTex;
		maxTexID = std::max(currentTexID, maxTexID);

		switchNextNode(texSetN);
	}
	if((int)type+1 < (int)TextureType::COUNT) m_offsets[(int)type+1] = maxTexID + 1;
}

void TextureSetHandler::frameReset() {
	for(unsigned int i = 0; i < m_textures.size(); i++) m_textures[i]->frameReset();
}

TextureSetHandler::~TextureSetHandler() {
	for(unsigned int i = 0; i < m_textures.size(); i++) delete (m_textures[i]);
}

TextureSet::TextureSet(Uint8 gfxLayer, bool composite, Uint8 defaultState) {
	for(int i = 0; i < Animation::maxUsers; i++) m_currentAnim[i] = -1;
	m_currentUser = 0;
	m_animated = false;
	m_gfxLayer = gfxLayer;
	m_composite = composite;
	m_defaultState = defaultState;
}

void TextureSet::addState(unsigned int stateID, Texture* texture) {
	while(stateID >= m_texStates.size()) {
		m_texStates.push_back(NULL);
	}
	m_texStates[stateID] = texture;
}

void TextureSet::addAnim(unsigned int animID, Animation* anim) {
	while(animID >= m_texAnims.size()) {
		m_texAnims.push_back(NULL);
	}
	m_texAnims[animID] = anim;
	m_animated = true;
}

Texture* TextureSet::getState(unsigned int stateID) {
#ifdef HEAVY_DEBUG
	if(!m_animated and stateID >= ANIMATION_OFFSET) std::cerr << "Error : request for animation " << stateID << " in non-animated texture";
	if(stateID < ANIMATION_OFFSET and stateID >= m_texStates.size()) std::cerr << "Error : request for out-of-bound state " << stateID;
#endif // HEAVY_DEBUG
	if(!m_animated) return m_texStates[stateID];
	if(stateID >= ANIMATION_OFFSET) {
		int animStateID = stateID - ANIMATION_OFFSET;

		if(m_currentAnim[m_currentUser] != animStateID && m_currentAnim[m_currentUser] != -1)	//Changed animation
			m_texAnims[m_currentAnim[m_currentUser]]->reset(m_currentUser);

		m_currentAnim[m_currentUser] = animStateID;
		return m_texAnims[animStateID]->getCurrentFrame(m_currentUser++);
	} else {
		if(m_currentAnim[m_currentUser] != -1) {
			m_texAnims[m_currentAnim[m_currentUser]]->reset(m_currentUser);
			m_currentAnim[m_currentUser] = -1;
		}
		m_currentUser++;
		return m_texStates[stateID];
	}
}

TextureSet::~TextureSet() {
	for(unsigned int i = 0; i < m_texStates.size(); i++) delete (m_texStates[i]);
	for(unsigned int i = 0; i < m_texAnims.size(); i++) delete (m_texAnims[i]);
}
