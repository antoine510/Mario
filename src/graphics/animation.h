#pragma once

#include "common.h"
#include "timer.h"

#include <SDL.h>

namespace Graphics {

class Animation {
public:
	Animation(SDL_Renderer* renderer, std::string path, int frameWidth, int frameCount, int delay);
	virtual ~Animation();

	virtual Texture* getCurrentFrame(int user);
	inline void reset(int user) { m_timer[user].stop(); }

	static constexpr int maxUsers = 10;

protected:
	std::vector<Texture*> m_frames;
	const int m_frameCount;
	const int m_delay;
	int m_currentFrame;
	LoopingTimer m_timer[maxUsers];

};

class NLAnimation : public Animation {
public:
	NLAnimation(SDL_Renderer* renderer, std::string path, int frameWidth, int frameCount, int delay, std::string fallbackPath = "");
	~NLAnimation();

	Texture* getCurrentFrame();

protected:
	Texture* m_fallback;
};

}

