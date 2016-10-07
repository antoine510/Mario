#include "background.h"
#include "../filetool.h"
#include <SDL.h>

using namespace Graphics;

Background::Background(int texID, int spanWidth, int spanSpeed)
{
    m_texID = texID;
    m_spanWidth = spanWidth;
    m_spanSpeed = spanSpeed;
    m_drawingPos = Rectangle(0, 0, 0, 0, FRAME_SCREEN);
}

void Background::refresh()
{
    m_drawingPos.addX(-(float)m_spanSpeed / 3);
    if(m_drawingPos.getX() < -m_spanWidth) m_drawingPos.addX(m_spanWidth);
}

RenderBackground::RenderBackground(GfxData* gfxData)
{
    m_gfxData = gfxData;
    std::cout << "Loading backgrounds\n";

	xmlDocPtr bgDoc = parseXML("textures/backgrounds.xml");
	xmlNodePtr bgN = xmlDocGetRootElement(bgDoc)->xmlChildrenNode;
	bypassText(bgN);

	while (bgN) {
		std::cout << "Assigning background\n";
		m_bgs.emplace_back(asInt(bgN, "texID"), asInt(bgN, "spanWidth"), asInt(bgN, "spanSpeed"));
		switchNextNode(bgN);
	}

	xmlFreeDoc(bgDoc);
}

void RenderBackground::renderBG(BackgroundID id)
{
    m_bgs[id].refresh();
    m_gfxData->textureSetHandler->getDefault(TEXTYPE_BACKGROUND, m_bgs[id].getTexID())->blit(m_bgs[id].getRect());
}

RenderBackground::~RenderBackground()
{
    m_bgs.clear();
}
