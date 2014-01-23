#include "StdAfx.h"
#include "Level.h"
#include "CollisionDetector.h"

namespace
{
    const float SceneSize = 100.f;
    const irr::fschar_t* LevelTexture = "levelTexture.psd";
    const irr::fschar_t* WallTexture = "level_04.gif";
}

Level::Level(irr::IrrlichtDevice* device)
: device_(device)
{
    using namespace irr;

    scene::ISceneManager* sceneManager = device->getSceneManager();

    // common scene node
    node_ = sceneManager->addSceneNode("empty");

    // prepare level scene
    scene::IBillboardSceneNode* node = sceneManager->addBillboardSceneNode( node_,
        core::dimension2d< f32 >(SceneSize, SceneSize) );

    node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setMaterialTexture( 0, device->getVideoDriver()->getTexture(LevelTexture) );
    node->setMaterialType( video::EMT_SOLID );

    // prepare some barriers
    const float HalfSize = SceneSize / 2.f;
    const float step = 10.f;
    for (float x = -HalfSize; x <= HalfSize; x += step)
    {
        AddCubeNode(x, 0, -HalfSize);
        AddCubeNode(-HalfSize, 0, x);
        AddCubeNode(x, 0, HalfSize);
        AddCubeNode(HalfSize, 0, x);
    }
    AddCubeNode(0, 0, 0, 20.f);

#ifdef _DEBUG
    // mark waypoints
    //waypoint_collection_t wayPoints = GetWayPoints();
    //for (int i = wayPoints.size(); i--; )
    //    AddCubeNode(wayPoints[i].X, wayPoints[i].Y, wayPoints[i].Z, 1.f);
#endif
}

Level::~Level()
{
}

void Level::AddCubeNode( float x, float y, float z, float side /*= 10.f*/)
{
    using namespace irr;
    scene::ISceneNode* node = device_->getSceneManager()->addCubeSceneNode(side,
        node_, -1, core::vector3df(x, y, z));

    //node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setMaterialTexture( 0, device_->getVideoDriver()->getTexture(WallTexture) );
    node->setMaterialType( video::EMT_SOLID );

    CollisionDetector::Instance().Register(node);
}

const Level::waypoint_collection_t& Level::GetWayPoints() const
{
    static std::vector<waypoint_t> WayPoints;
    if (WayPoints.size() == 0)
    {
        // fill with way points
        WayPoints.push_back(waypoint_t(30, 0, 20));
        WayPoints.push_back(waypoint_t(10, 0, 20));
        WayPoints.push_back(waypoint_t(-18, 0, 25));
        WayPoints.push_back(waypoint_t(-25, 0, -20));
        WayPoints.push_back(waypoint_t(20, 0, -27));
        WayPoints.push_back(waypoint_t(30, 0, -10));
    }

    return WayPoints;
}

