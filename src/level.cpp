#include "level.h"
#include "filetool.h"
#include "input.h"
#include "sound.h"
#include "physics/phyStack.h"
#include "ui/dialog.h"

Level::Level(std::string name)
{
    m_gameover = false;
    m_drawName = false;
    m_backgroundID = 0;
    gfxInterface->backgroundID = &m_backgroundID;
    soundStack->changeMusic(Musics::OVERWORLD);
    Physic::phyStack = new Physic::Stack();

	xmlDocPtr levelDoc = parseXML(name.c_str());
	xmlNodePtr levelN = xmlDocGetRootElement(levelDoc);
	bypassText(levelN);

	m_name = asString(levelN, "name");
	m_gameoverTimer.setDelay(2000);

	m_entities = new LevelEntities(levelN);

	dialog = NULL;

	xmlFreeDoc(levelDoc);
}

MarioMode Level::update(KeyStates* keystates)
{
    if(m_gameoverTimer.isFinished()) return MODE_MENU;               /**Back to main menu**/
    if (m_gameover && !m_gameoverTimer.isRunning()) {m_gameoverTimer.start();}   /**GAME OVER**/
    else if(keystates->isHoldEditor())
    {
        Graphics::viewport->setMode(Graphics::VPMODE_STATIC);
        timerStack->pauseTimers(true);
        return MODE_EDITOR;
    }
    else
    {
        if(dialog != NULL) {dialog->update();}
        m_entities->updateAll(keystates, &m_gameover);
        Physic::processCollisions();
        m_entities->updateGfxData();
    }
    return MODE_LEVEL;
}

Level::~Level()
{
    delete m_entities;
    delete Physic::phyStack;
}

