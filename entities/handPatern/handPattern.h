#ifndef HANDPATTERN_H_INCLUDED
#define HANDPATTERN_H_INCLUDED

#include "../../filetool.h"
#include "../../common.h"

#include "../../rectangle.h"
#include "../../path.h"
#include "../../graphics/gfxParameters.h"
#include "../../timer.h"
#include "hand.h"

typedef enum
{
	HPEVENTTYPE_WAIT = 0,
	HPEVENTTYPE_ENABLESECTION = 1,
	HPEVENTTYPE_DISABLESECTION = 2,
	HPEVENTTYPE_MOVEHAND = 3
} HPEventType;

struct HandPatternSection
{
    Rectangle rect;
    Rectangle drawRect;
    bool vertical;
    bool enabled;
    int phyStackPos;
    GfxParameters* gfxParameters;
};

struct HandPatternEvent
{
    int sectionID;
    unsigned int duration;
    Path2D path;
    HPEventType type;
    bool direct;
};

struct HandPatternQueue
{
    HandPatternEvent* events;
    const HandPatternEvent* current;
    HandPatternHand* hpHand;
    Timer* timer;
    int currentIdx;
    int eventCount;
    bool done;
};

class HandPattern
{
    public:
        HandPattern(std::string patternName);
        ~HandPattern();

        bool update();

    private:
        void readHPFile(const std::string& patternName);
        void readHPSections(xmlNodePtr sections);
        void readHPEvents(xmlNodePtr events, HandPatternQueue* eventQueue);
		static HPEventType eventTypeFromString(const std::string& name);
		static PathType pathTypeFromString(const std::string& str);

        void enableSection(HandPatternSection& section);
        void disableSection(HandPatternSection& section);

        void updateEventQueue(HandPatternQueue& eventQueue);
        void updateWait(HandPatternQueue& eventQueue);
        void updateEnableSection(HandPatternQueue& eventQueue);
        void updateDisableSection(HandPatternQueue& eventQueue);
        void updateMoveHand(HandPatternQueue& eventQueue);

        void initEvent(HandPatternQueue& eventQueue, const HandPatternEvent* event);

        void setSectionLength(int i, int v, bool direct = true);
        inline int getSectionLength(int i) const {return (m_sections[i].vertical) ? m_sections[i].drawRect.getH() : m_sections[i].drawRect.getW();}
        inline int getSectionStartLength(int i) const {return (m_sections[i].vertical) ? m_sections[i].rect.getH() : m_sections[i].rect.getW();}

        HandPatternSection* m_sections;
        int m_sectionCount;

        HandPatternQueue m_enableQueue;
        HandPatternQueue m_disableQueue;

        int m_type;
};

#endif // HANDPATTERN_H_INCLUDED
