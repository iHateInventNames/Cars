#pragma once
#include "actor.h"

class Car :
    public Actor
{
    typedef Actor base_t;

protected:
    irr::scene::ISceneManager* sceneManager_;

    irr::core::vector3df initialPosition_;
    irr::core::vector3df initialRotation_;

    static const float dSpeed;
    static const float dAngle;

public:
    Car( irr::IrrlichtDevice* device,
        const std::string& path = "",
        const std::string& texture = "");
    irr::core::vector3df InitialPosition() const { return initialPosition_; }
    void InitialPosition(irr::core::vector3df val) { initialPosition_ = val; }

    ~Car(void);
};
