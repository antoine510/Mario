#include "animation.h"
#include "texture.h"

using namespace Graphics;

Animation::Animation (SDL_Renderer* renderer, std::string path, int frameWidth, int frameCount, int delay)
{
    Surface rootSurface = Surface(path);
    Surface* subSurface;

    Rectangle clipRect(0, 0, frameWidth, rootSurface.getH());
    int i;

    for(i = 0; i < frameCount; i++)
    {
        m_frames.push_back(NULL);

        subSurface = rootSurface.getSubSurface(clipRect);
        m_frames[i] = new Texture(renderer, subSurface);
        delete subSurface;

        clipRect.addX(frameWidth);
    }
    m_frameCount = frameCount;
    m_delay = delay;
    for(int i = 0; i < MAX_ANIMATION_USER; i++) m_timer[i].setDelay(delay);
}

Texture* Animation::getCurrentFrame(int user)
{
    m_timer[user].start();
    m_currentFrame = m_timer[user].getLoopingCount() % m_frameCount;
    return m_frames[m_currentFrame];
}

Animation::~Animation()
{
    for(unsigned int i = 0; i < m_frames.size(); i++) delete (m_frames[i]);
}

NLAnimation::NLAnimation(SDL_Renderer* renderer, std::string path, int frameWidth, int frameCount, int delay, std::string fallbackPath)
            : Animation(renderer, path, frameWidth, frameCount, delay)
{
    m_fallback = new Texture(renderer, fallbackPath);
}

Texture* NLAnimation::getCurrentFrame()
{
    m_timer->start();
    m_currentFrame = m_timer->getLoopingCount();
    if (m_currentFrame >= m_frameCount)   {return m_fallback;}
    return m_frames[m_currentFrame];
}

NLAnimation::~NLAnimation ()
{
    delete m_fallback;
}

