#include "handPattern.h"
#include "../entityTypes.h"
#include "../../physics/phyStack.h"
#include "../../gfxInterface.h"

HandPattern::HandPattern(std::string patternName)
{
    m_type = TINDEX_GROUND;
    readHPFile(patternName);
    initEvent(m_enableQueue, m_enableQueue.current);
    initEvent(m_disableQueue, m_disableQueue.current);
}

void HandPattern::readHPFile(const std::string& patternName)
{
	std::string patentPath = "handPatterns/" + patternName + ".xml";

	xmlDocPtr handPatternDoc = parseXML(patentPath.c_str());
	xmlNodePtr hpSectionsN = xmlDocGetRootElement(handPatternDoc)->xmlChildrenNode;
	bypassText(hpSectionsN);

	readHPSections(hpSectionsN);
	switchNextNode(hpSectionsN);
	xmlNodePtr eventQueueN = hpSectionsN->children;
	bypassText(eventQueueN);

	readHPEvents(eventQueueN, &m_enableQueue);
	switchNextNode(eventQueueN);

	readHPEvents(eventQueueN, &m_disableQueue);

	xmlFreeDoc(handPatternDoc);
}

void HandPattern::readHPSections(xmlNodePtr sections)
{
	xmlNodePtr sectionN = sections->children;
	bypassText(sectionN);

    m_sectionCount = childCount(sections);
    m_sections = new HandPatternSection[m_sectionCount];

    int i = 0;
    HandPatternSection* t;
    while(sectionN)
    {
        t = &m_sections[i];
        t->rect = Rectangle(asInt(sectionN, "x"), asInt(sectionN, "y"),
                            asInt(sectionN, "width"), asInt(sectionN, "height"));
        t->vertical = (t->rect.getW() < t->rect.getH());

        //Adjustments necessary to obtain smooth levels
        if(t->vertical) {t->rect.addX(-1); t->rect.addH(-1);}
        else {t->rect.addY(-1); t->rect.addW(-1);}

        t->drawRect = t->rect;
        t->gfxParameters = new GfxParameters();
        t->gfxParameters->init(&t->drawRect, asInt(sections, "textureID"));
        t->enabled = false;

		switchNextNode(sectionN);
        i++;
    }
}

void HandPattern::readHPEvents(xmlNodePtr events, HandPatternQueue* eventQueue)
{
	xmlNodePtr eventN = events->children;
	bypassText(eventN);

    eventQueue->eventCount = childCount(events);
    eventQueue->events = new HandPatternEvent[eventQueue->eventCount];
    eventQueue->current = eventQueue->events;
    eventQueue->currentIdx = 0;
    eventQueue->done = false;

    int i = 0;
    while(eventN)
    {
		eventQueue->events[i].type = eventTypeFromString((const char*)eventN->name);
        switch (eventQueue->events[i].type)
        {
            case HPEVENTTYPE_WAIT:
                eventQueue->events[i].duration = asInt(eventN, "duration");
                break;
            case HPEVENTTYPE_ENABLESECTION:
            case HPEVENTTYPE_DISABLESECTION:
                eventQueue->events[i].sectionID = asInt(eventN, "sectionID");
                eventQueue->events[i].duration = asInt(eventN, "duration");
                eventQueue->events[i].direct = asBool(eventN, "direct");
                break;
            case HPEVENTTYPE_MOVEHAND:
                eventQueue->events[i].path = Path2D(pathTypeFromString(asString(eventN, "pathType")),
													Vect2(asInt(eventN, "x"), asInt(eventN, "y")),
													Vect2(asInt(eventN, "width"), asInt(eventN, "height")));
                eventQueue->events[i].duration = asInt(eventN, "duration");
                break;
        }
		switchNextNode(eventN);
        i++;
    }

    eventQueue->hpHand = new HandPatternHand(asInt(events, "handTextureID"), asInt(events, "handOffsetX"), asInt(events, "handOffsetY"));
    eventQueue->timer = new Timer();
}

HPEventType HandPattern::eventTypeFromString(const std::string& name)
{
	if (name == "EnableSection") return HPEVENTTYPE_ENABLESECTION;
	if (name == "DisableSection") return HPEVENTTYPE_DISABLESECTION;
	if (name == "Wait") return HPEVENTTYPE_WAIT;
	if (name == "MoveHand") return HPEVENTTYPE_MOVEHAND;
	return HPEVENTTYPE_WAIT;
}

PathType HandPattern::pathTypeFromString(const std::string& str)
{
	if (str == "linear") return LINEAR;
	if (str == "squared") return SQUARED;
	if (str == "amortized") return AMORTIZED;
	return LINEAR;
}

void HandPattern::enableSection(HandPatternSection& section)
{
    if(!section.enabled) {
        gfxInterface->gfxStack.addStack(section.gfxParameters);
        Physic::StaticParams t = {&section.drawRect, &m_type, NULL};
        section.phyStackPos = Physic::phyStack->addStack(t);

        section.enabled = true;
    }
}

void HandPattern::disableSection(HandPatternSection& section)
{
    if(section.enabled) {
        gfxInterface->gfxStack.deleteStack(section.gfxParameters);
        Physic::phyStack->deleteStatic(section.phyStackPos);

        section.enabled = false;
    }
}

void HandPattern::setSectionLength(int i, int v, bool direct)
{
    if(direct) {
        (m_sections[i].vertical) ? m_sections[i].drawRect.setH(v) : m_sections[i].drawRect.setW(v);
        m_sections[i].gfxParameters->updateBlitRects();
    }
    else {
        if(m_sections[i].vertical) {
            m_sections[i].drawRect.setY(m_sections[i].rect.getY() + (m_sections[i].rect.getH() - v)+1);
            m_sections[i].drawRect.setH(v);
        }
        else {
            m_sections[i].drawRect.setX(m_sections[i].rect.getX() + (m_sections[i].rect.getW() - v)+1);
            m_sections[i].drawRect.setW(v);
        }
        m_sections[i].gfxParameters->updateBlitRects();
    }
}

bool HandPattern::update()
{
    if(!m_enableQueue.done) updateEventQueue(m_enableQueue);
    if(!m_disableQueue.done) updateEventQueue(m_disableQueue);

    return m_disableQueue.done;
}

void HandPattern::updateEventQueue(HandPatternQueue& eventQueue)
{
    switch (eventQueue.current->type)
    {
        case HPEVENTTYPE_WAIT:
            updateWait(eventQueue);
            break;
        case HPEVENTTYPE_ENABLESECTION:
            updateEnableSection(eventQueue);
            break;
        case HPEVENTTYPE_DISABLESECTION:
            updateDisableSection(eventQueue);
            break;
        case HPEVENTTYPE_MOVEHAND:
            updateMoveHand(eventQueue);
            break;
    }
}

void HandPattern::updateWait(HandPatternQueue& eventQueue)
{
    if(!eventQueue.timer->isRunning())
    {
        eventQueue.current++;
        eventQueue.currentIdx++;
        if(eventQueue.currentIdx == eventQueue.eventCount) {eventQueue.done = true; return;}

        initEvent(eventQueue, eventQueue.current);
        updateEventQueue(eventQueue);
    }
}

void HandPattern::updateEnableSection(HandPatternQueue& eventQueue)
{
    if(!eventQueue.timer->isRunning())
    {
        int id = eventQueue.current->sectionID;
        setSectionLength(id, getSectionStartLength(id)+1, eventQueue.current->direct);

        eventQueue.current++;
        eventQueue.currentIdx++;
        if(eventQueue.currentIdx == eventQueue.eventCount) {eventQueue.done = true; return;}

        initEvent(eventQueue, eventQueue.current);
        updateEventQueue(eventQueue);
    }
    else
    {
        int id = eventQueue.current->sectionID;
        setSectionLength(id, int(eventQueue.timer->getEllapsedRatio() * getSectionStartLength(id)) +1, eventQueue.current->direct);
        if(eventQueue.current->direct) {
            eventQueue.hpHand->updatePos(m_sections[id].vertical, m_sections[id].drawRect, getSectionLength(id));
        }
        else {
            eventQueue.hpHand->updatePos(m_sections[id].vertical, m_sections[id].drawRect, 0);
        }
    }
}

void HandPattern::updateDisableSection(HandPatternQueue& eventQueue)
{
    if(!eventQueue.timer->isRunning())
    {
        disableSection(m_sections[eventQueue.current->sectionID]);

        eventQueue.current++;
        eventQueue.currentIdx++;
        if(eventQueue.currentIdx == eventQueue.eventCount) {eventQueue.done = true; return;}

        initEvent(eventQueue, eventQueue.current);
        updateEventQueue(eventQueue);
    }
    else
    {
        int id = eventQueue.current->sectionID;
        setSectionLength(id, int((1.0f-eventQueue.timer->getEllapsedRatio()) * getSectionStartLength(id)) + 1, !eventQueue.current->direct);
        if(!eventQueue.current->direct) {
            eventQueue.hpHand->updatePos(m_sections[id].vertical, m_sections[id].drawRect, getSectionLength(id));
        }
        else {
            eventQueue.hpHand->updatePos(m_sections[id].vertical, m_sections[id].drawRect, 0);
        }
    }
}

void HandPattern::updateMoveHand(HandPatternQueue& eventQueue)
{
    if(!eventQueue.timer->isRunning())
    {
        eventQueue.hpHand->updatePos(eventQueue.current->path.getValue(1));

        eventQueue.current++;
        eventQueue.currentIdx++;
        if(eventQueue.currentIdx == eventQueue.eventCount) {eventQueue.done = true; return;}

        initEvent(eventQueue, eventQueue.current);
        updateEventQueue(eventQueue);
    }
    else
    {
        eventQueue.hpHand->updatePos(eventQueue.current->path.getValue(eventQueue.timer->getEllapsedRatio()));
    }
}

void HandPattern::initEvent(HandPatternQueue& eventQueue, const HandPatternEvent* event)
{
    if(event->type == HPEVENTTYPE_ENABLESECTION)
    {
        int id = event->sectionID;
        eventQueue.hpHand->updatePos(!m_sections[id].vertical, m_sections[id].rect, 0);
        enableSection(m_sections[id]);
        setSectionLength(id, 1, event->direct);
    }
    else if(event->type == HPEVENTTYPE_DISABLESECTION)
    {
        int id = event->sectionID;
        eventQueue.hpHand->updatePos(!m_sections[id].vertical, m_sections[id].rect, 0);
    }
    else if(event->type == HPEVENTTYPE_MOVEHAND)
    {
        Vect2 vect = event->path.getValue(0);
        eventQueue.hpHand->updatePos(vect);
    }
    eventQueue.timer->setDelay(event->duration);
    eventQueue.timer->start();
}

HandPattern::~HandPattern()
{
    for (int i = 0; i < m_sectionCount; i++)
    {
        disableSection(m_sections[i]);
        delete m_sections[i].gfxParameters;
    }
    delete m_enableQueue.hpHand;                  //Disable the writing hand
    delete m_enableQueue.timer;
    delete m_disableQueue.hpHand;                 //Disable the erasing hand
    delete m_disableQueue.timer;

    delete [] m_sections;
    delete [] m_enableQueue.events;
    delete [] m_disableQueue.events;
}
