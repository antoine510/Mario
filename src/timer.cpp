#include "timer.h"
#include <SDL.h>

/**Global Var**/
TimerStack* timerStack;

Timer::Timer (unsigned int ticksDelay, bool pausable)
{
    m_ticksDelay = (int)(ticksDelay* PS/FPS);
    m_running = false;
    m_finished = false;
    m_paused = false;
    m_pausable = pausable;
}

void Timer::start()
{
    if (!m_running)
    {
        m_startTime = SDL_GetTicks();
        timerStack->addTimer(this);
        m_running = true;
        m_finished = false;
        m_paused = false;
    }
}

void Timer::pause(bool v)
{
    if(m_running && m_pausable)
    {
        if(v && !m_paused)
        {
            m_ellapsed = SDL_GetTicks() - m_startTime;
            m_paused = true;
        }
        else if(!v && m_paused)
        {
            m_startTime = SDL_GetTicks() - m_ellapsed;
            m_paused = false;
        }
    }
}

void Timer::stop()
{
    if(m_running)
    {
        m_running = false;
        m_ellapsed = 0;
        timerStack->deleteTimer(m_timerStackPos);
    }
}

void Timer::update()
{
    if(!m_paused)
    {
        m_ellapsed = SDL_GetTicks() - m_startTime;
        if (m_ellapsed > m_ticksDelay)
        {
            stop();
            m_finished = true;
        }
    }
}

void LoopingTimer::update()
{
	if(!m_paused)
		m_ellapsed = SDL_GetTicks() - m_startTime;
}

int LoopingTimer::getLoopingCount()
{
    if (m_running)
    {
        return m_ellapsed / m_ticksDelay;
    }
    return 0;
}


void TimerStack::addTimer(Timer* timer)
{
    m_timers.push_back(timer);
    timer->setStackPos(m_timers.size()-1);
}

void TimerStack::pauseTimers(bool v) const
{
    for(unsigned int i = 0; i < m_timers.size(); i++) m_timers[i]->pause(v);
}

void TimerStack::updateTimers() const
{
    for(unsigned int i = 0; i < m_timers.size(); i++) m_timers[i]->update();
}

void TimerStack::deleteTimer(unsigned int stackPos)
{
    if(stackPos >= m_timers.size())
        std::cerr << "Error : tried to delete timer at position " << stackPos << " which is out of bound\n";

    m_timers.erase(m_timers.begin() + stackPos);

    for(unsigned int i = 0; i < m_timers.size(); i++) m_timers[i]->setStackPos(i);  //Reset positions
}

