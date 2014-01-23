#include "StdAfx.h"
#include "BotCar.h"
#include <math.h>
#include <xutility>

namespace
{
    const float BotMaximumSpeed = .1f;
    const float AcceptableWaypointRadius = .5f;

}

BotCar::~BotCar(void)
{
}

BotCar::BotCar( irr::IrrlichtDevice* device, const Level& level )
: base_t(device)
, waypoints_(level.GetWayPoints())
{
    currentWaypoint_ = waypoints_.begin();
    MaximumSpeed(BotMaximumSpeed);
}

void BotCar::Move()
{
    using namespace irr;
    using namespace scene;
    using namespace core;

    core::vector3df position = node_->getPosition();
    core::vector3df toMove = *currentWaypoint_ - position;
    if (toMove.getLength() <= AcceptableWaypointRadius)
    {
        // waypoint riched, switch to next
        if(++currentWaypoint_ == waypoints_.end())
            currentWaypoint_ = waypoints_.begin();

        toMove = *currentWaypoint_ - node_->getPosition();
    }

    float speed = Speed();
    core::vector3df currentAcceleration = Direction() * speed;

    // calculate rotation angle
    const float DSpeed = dSpeed / 10;
    if(speed != 0.f)
    {
        core::vector3df targetAngles = toMove.getHorizontalAngle();
        float targetAngle = static_cast<float>(targetAngles.Y * core::DEGTORAD64);
        float curAngle = static_cast<float>(currentAcceleration.getHorizontalAngle().Y * core::DEGTORAD64);
        if (curAngle > PI)
            curAngle -= 2*PI;

        float sub = targetAngle - curAngle;
        if (sub > PI)
            sub -= 2*PI;
        float absSub = fabs(sub);
        float sign = sub / absSub;
        float absAngle = min(dAngle, absSub);
        if (absAngle > .000001f )
        {
            float randomEffect = (rand() % 100) * dAngle / 100 - dAngle / 2;
            Rotate(sign * absAngle + randomEffect);
        }

        sign = absSub >= core::HALF_PI ? -1.f : 1.f;
        float randomEffect = (rand() % 100) * DSpeed / 100 - DSpeed / 2;
        Accelerate(sign * min(DSpeed + randomEffect, toMove.getLength() + randomEffect));
    }
    else
    {
        Accelerate(DSpeed);
    }

    // inherit move processing
    base_t::Move();
}