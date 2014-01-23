#pragma once
#include <string>
#include <vector>
#include <ISceneManager.h>
#include "Car.h"
#include "KeysHandling.h"

class PlayerCar
    : public Car
{
    typedef Car base_t;

public:
    PlayerCar( irr::IrrlichtDevice* device,
        const std::string& path = "",
        const std::string& texture = "");

    void Move(); // override;
};
