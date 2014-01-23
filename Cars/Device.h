#pragma once
#include "singleton.h"

class Device :
    public Singleton<Device>
{
    irr::IrrlichtDevice* irrlichtDevice_;
    irr::video::IVideoDriver* driver_;
    irr::scene::ISceneManager* sceneManager_;
    irr::scene::ICameraSceneNode* cameraNode_;
    irr::scene::ISceneCollisionManager* collisionManager_;
public:
    irr::IrrlichtDevice* IrrlichtDevice() const { return irrlichtDevice_; }
    irr::video::IVideoDriver* Driver() const { return driver_; }
    irr::scene::ISceneManager* SceneManager() const { return sceneManager_; }
    irr::scene::ICameraSceneNode* CameraNode() const { return cameraNode_; }
    irr::scene::ISceneCollisionManager* CollisionManager() const { return collisionManager_; }

    Device();
};
