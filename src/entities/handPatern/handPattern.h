#ifndef HANDPATTERN_H_INCLUDED
#define HANDPATTERN_H_INCLUDED

#include "filetool.h"
#include "common.h"

#include "rectangle.h"
#include "path.h"
#include "graphics/gfxParameters.h"
#include "timer.h"
#include "hand.h"

struct HandPatternSection {
	Rectangle rect;
	Rectangle drawRect;
	bool vertical;
	bool enabled;
	int phyStackPos;
	GfxParameters* gfxParameters;
};


struct HandPatternQueue {
	HandPatternEvent* events;
	const HandPatternEvent* current;
	HandPatternHand* hpHand;
	Timer* timer;
	int currentIdx;
	int eventCount;
	bool done;
};

class HandPattern {
public:
	enum class EventType {
		WAIT = 0,
		ENABLE_SECTION = 1,
		DISABLE_SECTION = 2,
		MOVE_HAND = 3
	};

public:
	HandPattern(const std::string& patternName);
	~HandPattern();

	bool update();

private:
	void readHPFile(const std::string& patternName);
	void readHPSections(xmlNodePtr sections);
	void readHPEvents(xmlNodePtr events, HandPatternQueue* eventQueue);
	static EventType eventTypeFromString(const std::string& name);
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
	inline int getSectionLength(int i) const { return (m_sections[i].vertical) ? m_sections[i].drawRect.getH() : m_sections[i].drawRect.getW(); }
	inline int getSectionStartLength(int i) const { return (m_sections[i].vertical) ? m_sections[i].rect.getH() : m_sections[i].rect.getW(); }

	HandPatternSection* m_sections;
	int m_sectionCount;

	HandPatternQueue m_enableQueue;
	HandPatternQueue m_disableQueue;

	int m_type;
};

struct HandPatternEvent {
	int sectionID;
	unsigned int duration;
	Path2D path;
	HandPattern::EventType type;
	bool direct;
};


#endif // HANDPATTERN_H_INCLUDED
