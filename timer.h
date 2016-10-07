#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "common.h"

class Timer
{
    public:
        Timer(unsigned int ticksDelay = 0, bool pausable = true);
        virtual ~Timer() {stop();}

        void start();
        void pause(bool v);
        void stop();
        inline void restart() {stop(); start();}

        virtual void update();

        inline bool isRunning() const {return m_running;}
        inline bool isFinished() const {return m_finished;}

        inline void setDelay(unsigned int delay) {m_ticksDelay = delay;}
        float getEllapsedRatio() const {return m_ellapsed / (float)m_ticksDelay;}
        unsigned int getEllapsed() const {return m_ellapsed;}

        inline void setStackPos(unsigned int pos) {m_timerStackPos = pos;}

    protected:
        unsigned int m_startTime;
        unsigned int m_ellapsed;
        unsigned int m_ticksDelay;
        bool m_running;
        bool m_finished;
        bool m_paused;
        bool m_pausable;

        unsigned int m_timerStackPos;
};

class LoopingTimer : public Timer
{
    public:
        LoopingTimer(unsigned int ticksDelay = 0, bool pausable = true) : Timer(ticksDelay, pausable) {}
        virtual ~LoopingTimer() {}

        virtual void update();

        int getLoopingCount();

    protected:

};

class TimerStack
{
    public:
        void addTimer(Timer* timer);
        void deleteTimer(unsigned int stackPos);

        void pauseTimers(bool v) const;
        void updateTimers() const;

    private:
        std::vector<Timer*> m_timers;           //Sorted stack
};

extern TimerStack* timerStack;

#endif // TIMER_H_INCLUDED
