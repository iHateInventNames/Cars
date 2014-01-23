#pragma once
#include "SceneNode.h"
#include <vector3d.h>
#include <IEventReceiver.h>

class Actor
    : SceneNode
{
    irr::core::vector3df direction_;
    float speed_;
    float maximumSpeed_;
    float minimumSpeed_;

protected:
    irr::scene::ISceneNode* node_;

    irr::core::vector3df Direction() const { return direction_; }
    float Speed() const { return speed_; }
    float MaximumSpeed() const { return maximumSpeed_; }
    void MaximumSpeed(float val) { maximumSpeed_ = val; }

public:
    Actor(const irr::core::vector3df initialDirection);

    irr::core::vector3df InitialDirection() const { return direction_; }
    void InitialDirection(irr::core::vector3df val) { direction_ = val; }

    virtual void Move();
    void Accelerate(const float dSpeed);

    void Rotate(float angle);

    irr::scene::ISceneNode* Node();
};
