#pragma once
#include "singleton.h"
#include <IrrlichtDevice.h>
#include <Keycodes.h>

class KeysHandling
    : public Singleton<KeysHandling>
    , irr::IEventReceiver
{
public:
    KeysHandling();
    ~KeysHandling();

    // implement IEventReceiver methods
    bool OnEvent( const irr::SEvent& e );

    static void Register(irr::IrrlichtDevice* device);
    static bool IsKeyPressed(irr::EKEY_CODE keyCode);
};
