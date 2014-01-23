// Cars.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Cars.h"
#include "PlayerCar.h"
#include "KeysHandling.h"
#include "Level.h"
#include "BotCar.h"
#include "CollisionDetector.h"
#include "Device.h"
#include <algorithm>

namespace //params
{
    const size_t BotsCount = 3;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    using namespace irr;
    using namespace scene;

    // create 3d device
    IrrlichtDevice* device = Device::Instance().IrrlichtDevice();

    // create level details
    Level level(device);

    // game actors collection
    typedef Actor*    game_item_t;
    typedef std::vector<game_item_t>    actors_collection_t;
    actors_collection_t actors;

    // create player car
    PlayerCar* player = new PlayerCar(device);
    player->InitialDirection(irr::core::vector3df(0, 0, 1.f));
    player->InitialPosition(core::vector3df(25.f, 0, 5.f));
    player->Node()->setPosition(player->InitialPosition());
    actors.push_back(game_item_t(player));
    CollisionDetector::Instance().Register(player->Node());

    // fill with bots
    for (int i = BotsCount; i--; )
    {
        BotCar* bot = new BotCar(device, level);
        bot->Node()->setPosition(core::vector3df(35.f - i*2, 0, static_cast<float>(-i)));
        bot->InitialDirection(core::vector3df(0, 0, 1));
        actors.push_back(bot);
        CollisionDetector::Instance().Register(bot->Node());
    }

    // start keys handling
    KeysHandling::Register(device);
  
    // start game loop
    ICameraSceneNode* cameraNode = Device::Instance().CameraNode();
    video::IVideoDriver* driver = Device::Instance().Driver();
    ISceneManager* sceneManager = Device::Instance().SceneManager();
    sceneManager->addLightSceneNode(0, core::vector3df(0,50,0));
    while(device->run())
    {
        for (actors_collection_t::iterator it = actors.begin(); it != actors.end(); ++it)
        {
            (*it)->Move();
        }

        const core::vector3df& playerPosition = player->Node()->getPosition();
        cameraNode->setPosition(core::vector3df(playerPosition.X,
            cameraNode->getPosition().Y,
            playerPosition.Z));
        cameraNode->setTarget(playerPosition);
        
        driver->beginScene(true, true, video::SColor(255,0,0,0));
        sceneManager->drawAll();
        driver->endScene();
    }

    // cleanup
    for (actors_collection_t::iterator it = actors.begin(); it != actors.end(); ++it)
    {
        delete *it;
    }

    return 0;
}

