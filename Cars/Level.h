#pragma once
#include "SceneNode.h"
#include <IrrlichtDevice.h>
#include <vector>

class Level
    : SceneNode
{
    irr::IrrlichtDevice* device_;

    void AddCubeNode(float x, float y, float z, float side = 10.f);
public:
    typedef irr::core::vector3df    waypoint_t;
    typedef std::vector<waypoint_t> waypoint_collection_t;

    Level(irr::IrrlichtDevice* device);
    virtual ~Level();

    virtual const waypoint_collection_t& GetWayPoints() const;

};
