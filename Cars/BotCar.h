#pragma once
#include "Car.h"
#include "Level.h"

class BotCar :
    public Car
{
    typedef Car base_t;
    const Level::waypoint_collection_t& waypoints_;
    Level::waypoint_collection_t::const_iterator currentWaypoint_;

public:
    BotCar(irr::IrrlichtDevice* device, const Level& level);
    ~BotCar(void);

    void Move();
};
