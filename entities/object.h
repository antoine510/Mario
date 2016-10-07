#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "../common.h"
#include "../rectangle.h"
#include "entityTypes.h"
#include "../vector.h"
#include "../graphics/gfxParameters.h"
#include "../gfxInterface.h"
#include "../physics/phyStack.h"

#define MAX_DOWN_SPEED 300
#define MIN_SPEED 2
#define FORWARD_SPEED 50


class Object
{
    public:
        Object(Rectangle* rectangle, int texID);
        virtual ~Object();

        inline void updateGfxData() {m_gfxParameters.setState(textureState());}
        inline void updateGfxParams() {m_gfxParameters.updateBlitRects();}

        inline Rectangle* getObjectRectangle() const {return m_rectangle;}
        inline int getType() const {return m_type;}
        inline bool hasToBeDeleted() const {return m_hasToBeDeleted;}
        inline void destroy() {m_hasToBeDeleted = true;}

    protected:
        virtual int textureState() = 0;

        Rectangle* m_rectangle;
        GfxParameters m_gfxParameters;
        int m_phyStackPos;                          //m_phyParameters

        int m_type;
        bool m_hasToBeDeleted;
};

class DynamicObject : public Object
{
    public:
        DynamicObject(Rectangle* rectangle, int TexID);
        virtual ~DynamicObject();

        void stop(Rectangle* rect, int collDirection);
        inline void go() {m_liesOnFloor = false;}
        void goBack(int collDirection);

        virtual void update();
        virtual void kill();
        virtual void collide(const Physic::CollisionParams* collParams, int collDirection) = 0;

        inline bool isAlive() const {return m_isAlive;}
        inline CollisionHandler* getCH() {return m_CH;}

    protected:
        virtual int textureState() = 0;

        Vect2 m_speed;
        TYPE_TYPE m_collideWith;
        CollisionHandler* m_CH;

        bool m_liesOnFloor;
        bool m_isAlive;
        int m_forwardDirection;
};

class StaticObject : public Object
{
    public:
        StaticObject(Rectangle* rectangle, int TexID);
        virtual ~StaticObject();

    protected:
        virtual int textureState() {return 0;}
};

class Ground : public StaticObject
{
    public:
        Ground(Rectangle* rectangle, int TexID);
        virtual ~Ground();

    protected:
         virtual int textureState() {return 0;}
};

class Decor : public Object
{
    public:
        Decor(Rectangle* rectangle, int TexID, int layer);
        virtual ~Decor();

    protected:
        virtual int textureState() {return 0;}
};

#endif // OBJECT_H_INCLUDED
