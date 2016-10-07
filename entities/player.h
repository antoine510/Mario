#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../common.h"
#include "object.h"


#define MIN_SIDE_SPEED 10
#define MAX_SIDE_SPEED 70
#define MAX_SIDE_SPEED_SPEEDING 50
#define SIDE_SPEED_BRAKE 300/PS
#define PLAYER_JUMP_FORCE 300.0f
#define PLAYER_SIDE_ACCELERATION 150.0f
#define PLAYER_SPEED_SIDE_ACCELERATION 180.0f

#define PLAYER_HURT_TIMER 1000
#define PLAYER_FIRING_TIMER 400
#define PLAYER_FLASH_TIMER 100
#define PLAYER_DEATH_TIMER 1000

#define LIFE_LITTLE_MARIO 0
#define LIFE_BIG_MARIO 1
#define LIFE_FIRE_MARIO 2

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

        void setLife(int newLife);
        inline void subLife() {setLife(m_life -1);}
        void addLife();

        void addCoin(int amount);

        virtual void kill();
        virtual void collide(const Physic::CollisionParams* collParams, int collDirection);

    private:
        virtual int textureState();

        std::string m_name;
        int m_life;
        int m_coinNumber;
        int m_direction;
        Timer* m_hurtTimer;
        Timer* m_firingTimer;
        Timer* m_killTimer;
        LoopingTimer* m_flashTimer;

        bool m_isSpeeding;
        bool m_isLeaning;

        unsigned char m_keySet;
};

#endif // PLAYER_H_INCLUDED
