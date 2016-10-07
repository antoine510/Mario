#ifndef TRIGGER_H_INCLUDED
#define TRIGGER_H_INCLUDED

#include "../common.h"
#include "object.h"
#include "../worldEntities.h"

enum TriggerType {HAND_PATTERN = 0, DIALOG = 1, END = 2};

class Trigger : public StaticObject
{
    public:
        Trigger(Rectangle* rectangle, int texID = 0);
        ~Trigger();

        virtual void activate() = 0;
        inline TriggerType getTriggerType() const {return m_triggerType;}

    protected:
        TriggerType m_triggerType;
};

class HPTrigger : public Trigger
{
    public:
        HPTrigger(Rectangle* rectangle, const std::string& hpFile, LevelEntities* parent);

        virtual void activate();

    protected:
        LevelEntities* m_parent;
        std::string m_hpFile;
};

class DialogTrigger : public Trigger
{
    public:
        DialogTrigger(Rectangle* rectangle, const std::string& dialogFile);

        virtual void activate();

    protected:
        std::string m_dialogFile;
};

class EndTrigger : public Trigger
{
    public:
        EndTrigger(Rectangle* rectangle);

        virtual void activate();

    protected:
        std::string m_dialogFile;
};

#endif // TRIGGER_H_INCLUDED
