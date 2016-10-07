#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "../common.h"
#include "../timer.h"
#include "textureSet.h"
#include <SDL.h>

namespace Graphics{
class Animation
{
    public:
        Animation (SDL_Renderer* renderer, std::string path, int frameWidth, int frameCount, int delay);
        virtual ~Animation();

        virtual Texture* getCurrentFrame(int user);
        inline void reset(int user) {m_timer[user].stop();}

    protected:
        std::vector<Texture*> m_frames;
        int m_frameCount;
        int m_delay;
        int m_currentFrame;
        LoopingTimer m_timer[MAX_ANIMATION_USER];

};

class NLAnimation : public Animation
{
    public:
        NLAnimation(SDL_Renderer* renderer, std::string path, int frameWidth, int frameCount, int delay, std::string fallbackPath = "");
        ~NLAnimation();

        Texture* getCurrentFrame();

    protected:
        Texture* m_fallback;
};

}

#endif // ANIMATION_H_INCLUDED
