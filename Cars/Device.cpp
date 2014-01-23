#include "StdAfx.h"
#include "Device.h"


namespace //params
{
    const float CameraHeight = 20.f;
    const irr::core::dimension2d<irr::u32> WindowSize(1024,768);
}

Device::Device()
{
    using namespace irr;
    using namespace scene;

    irrlichtDevice_ = createDevice(video::EDT_OPENGL, WindowSize//, 32, true
        );
    if (!irrlichtDevice_) exit(-1);

    // create engine and camera
    irrlichtDevice_->setWindowCaption(L"Cars");
    driver_ = irrlichtDevice_->getVideoDriver();
    sceneManager_ = irrlichtDevice_->getSceneManager();
    cameraNode_ = sceneManager_->addCameraSceneNode(0, 
        core::vector3df(0,CameraHeight,0), 
        core::vector3df(0,0,0));
    collisionManager_ = sceneManager_->getSceneCollisionManager();
}