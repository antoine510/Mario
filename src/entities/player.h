#pragma once

#include "../common.h"
#include "object.h"

class Player : public DynamicObject
{
    public:
        Player(std::string name, Rectangle* rectangle, int TexID, int keySet);
        virtual ~Player();

        void update(KeyStates* keystates);
        void reshape();
        void jump(bool enableSound);
        void hurt();
        void fire();
        bool canStandUp();

        inline void subLife() { 
			if (m_life == LITTLE_MARIO) kill();
			else m_life = LifeLevel(m_life - 1);
			reshape();
		}
        void addLife();

        void addCoin(int amount);

        virtual void kill();
        virtual void collide(const Physic::CollisionParams* collParams, int collDirection);

    private:
		enum LifeLevel {
			LITTLE_MARIO,
			BIG_MARIO,
			FIRE_MARIO
		};

        virtual int textureState();

		static constexpr int m_hurtTimerTime = 1000, m_firingTimerTime = 400, m_flashTimerTime = 100, m_deathTimerTime = 1000;
		static constexpr float m_jumpForce = 300.0f, m_sideAcceleration = 150.0f, m_sideAccelerationSpeeding = 330.0f;
		static constexpr float m_sideSpeedBrake = 300.0f/PS, m_minSideSpeed = 10.0f, m_maxSideSpeed = 70.0f, m_maxSideSpeedSpeeding = 120.0f;

        std::string m_name;
        LifeLevel m_life = BIG_MARIO;
        int m_coinNumber = 0;
        int m_direction = HDIRECTION_R;
        Timer* m_hurtTimer;
        Timer* m_firingTimer;
        Timer* m_killTimer;
        LoopingTimer* m_flashTimer;

        bool m_isSpeeding = false;
        bool m_isLeaning = false;

        unsigned char m_keySet;
};

