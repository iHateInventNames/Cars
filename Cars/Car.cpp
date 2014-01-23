#include "StdAfx.h"
#include "Car.h"


namespace
{
    const irr::fschar_t* Mesh = "cpp_home_test2_res/car.3ds";
    const irr::fschar_t* LevelTexture = "cpp_home_test2_res/car_05_clean.psd";
}

const float Car::dSpeed = 0.002f;
const float Car::dAngle = .015f;


Car::Car(irr::IrrlichtDevice* device, const std::string& path, const std::string& texture )
: base_t(irr::core::vector3df(0, 0, -1.f))
, sceneManager_(device->getSceneManager())
{
    const irr::fschar_t* meshPath = path.empty() ? Mesh : path.c_str();
    const irr::fschar_t* meshTexture = texture.empty() ? LevelTexture : texture.c_str();

    node_ = sceneManager_->addAnimatedMeshSceneNode(
        sceneManager_->getMesh(meshPath));

    if (node_)
    {
        node_->setMaterialTexture(0, device->getVideoDriver()->getTexture(meshTexture));
        node_->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        initialPosition_ = node_->getPosition();
        initialRotation_ = node_->getRotation();
    }

    // events processing
    //device->setEventReceiver(this);
}

Car::~Car(void)
{
}
