#include "trigger.h"
#include "../ui/dialog.h"
#include "../sound.h"

Trigger::Trigger(Rectangle* rectangle, int texID) : StaticObject(rectangle, texID)
{
    m_type = TINDEX_TRIGGER;
    Physic::StaticParams t = {m_rectangle, &m_type, this};
    m_phyStackPos = Physic::phyStack->addStack(t);
}

Trigger::~Trigger()
{
    Physic::phyStack->deleteStatic(m_phyStackPos);
}

HPTrigger::HPTrigger(Rectangle* rectangle, const std::string& hpFile, LevelEntities* parent) : Trigger(rectangle)
{
    m_triggerType = HAND_PATTERN;
    m_parent = parent;
    m_hpFile = hpFile;
    gfxInterface->gfxStack.deleteStack(&m_gfxParameters);
}

void HPTrigger::activate()
{
    m_parent->setHandPatern(m_hpFile);
    destroy();
}

DialogTrigger::DialogTrigger(Rectangle* rectangle, const std::string& dialogFile) : Trigger(rectangle)
{
    m_triggerType = DIALOG;
    m_dialogFile = dialogFile;
    gfxInterface->gfxStack.deleteStack(&m_gfxParameters);
}

void DialogTrigger::activate()
{
    dialog = new Dialog(m_dialogFile);
    destroy();
}

EndTrigger::EndTrigger(Rectangle* rectangle) : Trigger(rectangle, 4)
{
    m_triggerType = END;
}

void EndTrigger::activate()
{
    soundStack->addToStack(Sounds::WIN);
    soundStack->stopMusic();
    destroy();
}

