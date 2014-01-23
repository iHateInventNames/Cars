#include "StdAfx.h"
#include "Actor.h"
#include "CollisionDetector.h"
#include <assert.h>

namespace
{
    const irr::core::vector3df NullVector(0.,0.,0.);
    const float DefaultMaxSpeed = .25f;
    const float DefaultMinSpeed = -.05f;
}

Actor::Actor( const irr::core::vector3df initialDirection )
: direction_(initialDirection)
, speed_(0.f)
, maximumSpeed_(DefaultMaxSpeed)
, minimumSpeed_(DefaultMinSpeed)
{
    assert(initialDirection != irr::core::vector3df(NullVector));
}

void Actor::Accelerate( const float dSpeed )
{
    speed_+=dSpeed;
    if (speed_ > maximumSpeed_)
        speed_ = maximumSpeed_;
    if (speed_ < minimumSpeed_)
        speed_ = minimumSpeed_;
}

void Actor::Rotate( float angle )
{
    const float RotationAccelerationCoeficient = 400;
    angle *= speed_ * RotationAccelerationCoeficient;
    direction_.rotateXZBy(-angle);
    direction_.normalize();
}

void Actor::Move()
{
    if (speed_ != 0.f)
    {
        using namespace irr;
        assert(!CollisionDetector::Instance().HasCollisions(node_));

        // move & rotate
        core::vector3df inititalPosition = node_->getPosition();
        core::vector3df inititalRotation = node_->getRotation();
        node_->setPosition(inititalPosition + direction_.normalize() * speed_);
        core::vector3df horizontalAngle = direction_.getHorizontalAngle();
        node_->setRotation(core::vector3df(horizontalAngle.X, horizontalAngle.Y + 180, horizontalAngle.Z));

        if (CollisionDetector::Instance().HasCollisions(node_))
        {
            const int MoveTryCount = 15;
            for (int i = MoveTryCount; CollisionDetector::Instance().HasCollisions(node_) && i--; )
            {
                node_->setPosition(node_->getPosition() + direction_.normalize() * speed_);
            }

            node_->setPosition(inititalPosition);
            node_->setRotation(inititalRotation);
            speed_ = 0.f;
        }

        assert(!CollisionDetector::Instance().HasCollisions(node_));
    }
}

irr::scene::ISceneNode* Actor::Node()
{
    return node_;
}