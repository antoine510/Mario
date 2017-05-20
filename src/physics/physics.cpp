#include "physics.h"
#include "sweepAndPrune.h"
#include "../rectangle.h"
#include "../vector.h"
#include "collisionHandler.h"
#include "../entities/entitiesHandler.h"
#include "../entities/object.h"
#include "phyStack.h"

using namespace Physic;

void Physic::processCollisions()
{
    phyStack->updateStack();

    const std::vector<CollisionParams>& staticParams = phyStack->getStaticParams();
    const std::vector<CollisionParams>& dynamicParams = phyStack->getDynamicParams();
    const std::vector< std::pair<SAPCandidate, SAPCandidate> >& candidates = phyStack->getCandidates();
    std::vector< std::pair<SAPCandidate, SAPCandidate> >::const_iterator candidateIt;

    for(candidateIt = candidates.begin(); candidateIt != candidates.end(); ++candidateIt)
    {
        if(candidateIt->first.isDynamic && candidateIt->second.isDynamic) {
            const CollisionParams& dyn1 = dynamicParams[candidateIt->first.phyStackPos], &dyn2 = dynamicParams[candidateIt->second.phyStackPos];
            if(dyn1.static_.rect != nullptr && dyn2.static_.rect != nullptr
			&& EntitiesHandler::matchMasks(*dyn2.static_.type, *dyn1.dynamic.collisionMask)
            && EntitiesHandler::matchMasks(*dyn1.static_.type, *dyn2.dynamic.collisionMask))
                dynamicCollision(dyn1, dyn2);
        }
        else if(candidateIt->first.isDynamic) {
            const CollisionParams& dyn = dynamicParams[candidateIt->first.phyStackPos], &sta = staticParams[candidateIt->second.phyStackPos];
            if(EntitiesHandler::matchMasks(*sta.static_.type, *dyn.dynamic.collisionMask)) staticCollision(dyn, sta);
        }
        else {
            const CollisionParams& dyn = dynamicParams[candidateIt->second.phyStackPos], &sta = staticParams[candidateIt->first.phyStackPos];
            if(EntitiesHandler::matchMasks(*sta.static_.type, *dyn.dynamic.collisionMask)) staticCollision(dyn, sta);
        }
    }

    for (std::vector<CollisionParams>::const_iterator dynamicIt = dynamicParams.begin(); dynamicIt != dynamicParams.end(); ++dynamicIt)
    {
        if((*dynamicIt).static_.rect != NULL)
        {
            ((DynamicObject*)((*dynamicIt).static_.parent))->getCH()->process();
        }
    }
}

void Physic::setMyStaticColls(int myStackPos)
{
    const CollisionParams& objParams = phyStack->getDynamicParams()[myStackPos];
    const std::vector<CollisionParams>& staticParamsRef = phyStack->getStaticParams();
    std::vector<CollisionParams>::const_iterator staticIt;

    for (staticIt = staticParamsRef.begin(); staticIt != staticParamsRef.end(); ++staticIt)
    {
        if((*staticIt).static_.rect != NULL
        && EntitiesHandler::matchMasks(*(*staticIt).static_.type, *objParams.dynamic.collisionMask))
        {
            Physic::staticCollision(objParams, *staticIt);
        }
    }
}

bool Physic::overlapTest(Rectangle* rectA, Rectangle* rectB)    /**WORKING**/
{
    if ((rectA->getFX()         >=   rectB->getOffsetFW()    ) ||
        (rectA->getOffsetFW()   <=   rectB->getFX()          ) ||
        (rectA->getFY()         >=   rectB->getOffsetFH()    ) ||
        (rectA->getOffsetFH()   <=   rectB->getFY()          ))
    {
        return false;
    }
    return true;
}

int Physic::staticDirectionTest(Rectangle* rectA, Rectangle* rectB, Vect2& velocityA)   /**WORKING**/
{
    if (velocityA.getX() < 0)
    {
        if (velocityA.getY() < 0)
        {
            if ((velocityA.getX()*(rectB->getOffsetFH() - rectA->getFY())) > (velocityA.getY()*(rectB->getOffsetFW() - rectA->getFX())))
            {
                return DIRECTION_DOWN;
            }
            else
            {
                return DIRECTION_LEFT;
            }
        }
        else
        {
            if ((velocityA.getX()*(rectB->getFY() - rectA->getOffsetFH())) > (velocityA.getY()*(rectB->getOffsetFW() - rectA->getFX())))
            {
                return DIRECTION_LEFT;
            }
            else
            {
                return DIRECTION_UP;
            }
        }
    }
    else if (velocityA.getX() > 0)
    {
        if (velocityA.getY() < 0)
        {
            if ((velocityA.getX()*(rectA->getFY() - rectB->getOffsetFH())) < (velocityA.getY()*(rectA->getOffsetFW() - rectB->getFX())))
            {
                return DIRECTION_RIGHT;
            }
            else
            {
                return DIRECTION_DOWN;
            }
        }
        else
        {
            if ((velocityA.getX()*(rectA->getOffsetFH() - rectB->getFY())) < (velocityA.getY()*(rectA->getOffsetFW() - rectB->getFX())))
            {
                return DIRECTION_UP;
            }
            else
            {
                return DIRECTION_RIGHT;
            }
        }
    }
    else
    {
        if(velocityA.getY() < 0)
        {
            return DIRECTION_DOWN;
        }
        else if(velocityA.getY() > 0)
        {
            return DIRECTION_UP;
        }
        else
        {
            return DIRECTION_NONE;
        }
    }
}

int Physic::dynamicDirectionTest(Rectangle* rectA, Rectangle* rectB, Vect2& velocityA, Vect2& velocityB)    /**WORKING**/
{
    if (velocityA >= velocityB)
    {
        Vect2 deltav = (velocityA - velocityB);
        return staticDirectionTest(rectA, rectB, deltav);
    }
    else
    {
        Vect2 deltav = (velocityB - velocityA);
        return Vect2::invDirection(staticDirectionTest(rectB, rectA, deltav));
    }
}

void Physic::staticCollision(const CollisionParams& dynamicParams, const CollisionParams& staticParams)
{
    if (overlapTest(dynamicParams.static_.rect, staticParams.static_.rect))
    {
        int collDirection = staticDirectionTest(dynamicParams.static_.rect, staticParams.static_.rect, *dynamicParams.dynamic.velocity);

        ((DynamicObject*)(dynamicParams.static_.parent))->getCH()->addCollision(staticParams, collDirection);
    }
}

void Physic::dynamicCollision(const CollisionParams& dynamicParams, const CollisionParams& dynamicParams2)
{
    if (overlapTest(dynamicParams.static_.rect, dynamicParams2.static_.rect))
    {
        int collDirection = dynamicDirectionTest(dynamicParams.static_.rect, dynamicParams2.static_.rect,
                                                 *dynamicParams.dynamic.velocity, *dynamicParams2.dynamic.velocity);

        ((DynamicObject*)(dynamicParams.static_.parent))->getCH()->addCollision(dynamicParams2, collDirection);
        ((DynamicObject*)(dynamicParams2.static_.parent))->getCH()->addCollision(dynamicParams, Vect2::invDirection(collDirection));
    }
}

