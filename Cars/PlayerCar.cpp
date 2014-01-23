#include "StdAfx.h"
#include "PlayerCar.h"
#include "Menu.h"
#include <EMaterialFlags.h>


PlayerCar::PlayerCar( irr::IrrlichtDevice* device, 
                     const std::string& path /*= ""*/,
                     const std::string& texture /*= ""*/ )
 : base_t(device, path, texture)
{
    //MaximumSpeed(.5f);
}

void PlayerCar::Move() /* overridden */
{
    // TODO : implement time based calculations

    using namespace irr;

    if (KeysHandling::IsKeyPressed(KEY_UP))
        Accelerate(dSpeed);
    else if (KeysHandling::IsKeyPressed(KEY_DOWN))
        Accelerate(-dSpeed);
    else
    {
        float accelerationLength = Speed();
        if (accelerationLength > 0.f)
            Accelerate(max(-dSpeed / 5, -accelerationLength ));
    }   

    if (KeysHandling::IsKeyPressed(KEY_RIGHT))
        Rotate(dAngle);

    if (KeysHandling::IsKeyPressed(KEY_LEFT))
        Rotate(-dAngle);

    if (KeysHandling::IsKeyPressed(KEY_KEY_R))
    {
        node_->setRotation(initialRotation_);
        node_->setPosition(initialPosition_);
        Accelerate(-Speed());
    }

    if (KeysHandling::IsKeyPressed(KEY_ESCAPE) ||
        KeysHandling::IsKeyPressed(KEY_KEY_P) ||
        KeysHandling::IsKeyPressed(KEY_PAUSE))
    {
        // show menu
        Menu().Show();
    }

    base_t::Move();
}