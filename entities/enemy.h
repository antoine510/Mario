#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "../common.h"
#include "object.h"
#include "../timer.h"

#define WALKING_ANIMATION_SPEED 380
#define KOOPA_SHELL_SPEED_BOOST 100

class Enemy : public DynamicObject
{
    public:
        Enemy(Rectangle* rectangle, int TexID);
        virtual ~Enemy();

        virtual void update();
        virtual void kill();
        virtual void collide(const Physic::CollisionParams* collParams, int collDirection) = 0;

    protected:
        virtual int textureState() = 0;

        Timer m_killTimer;
};

class Goomba : public Enemy
{
    public:
        Goomba(Rectangle* rectangle, int TexID);
        virtual ~Goomba();

        virtual void kill();
        virtual void collide(const Physic::CollisionParams* collParams, int collDirection);

    private:
        virtual int textureState();

        LoopingTimer m_walkTimer;
};

class Koopa : public Enemy
{
    public:
        Koopa(Rectangle* rectangle, int TexID);
        virtual ~Koopa();

        virtual void collide(const Physic::CollisionParams* collParams, int collDirection);

        inline bool isAggressive() const {return m_isShellMoving;}

    private:
        virtual int textureState();

        bool m_isShell;
        bool m_isShellMoving;
};


#endif // ENEMY_H_INCLUDED
