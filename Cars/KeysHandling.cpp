#include "StdAfx.h"
#include "KeysHandling.h"
#include <vector>

namespace
{
    const int KeysCount = 256;
    std::vector<bool> keyStates_(KeysCount);
}


KeysHandling::KeysHandling()
{

}

void KeysHandling::Register( irr::IrrlichtDevice* device )
{
    device->setEventReceiver(
        &static_cast<irr::IEventReceiver&>(KeysHandling::Instance()));
}

KeysHandling::~KeysHandling()
{

}

bool KeysHandling::OnEvent( const irr::SEvent& e )
{
    const float dSpeed = 0.001f;
    const float dAngle = .1f;
    using namespace irr;
    bool processed = e.EventType == EET_KEY_INPUT_EVENT;
    if(processed)
    {
        keyStates_[e.KeyInput.Key] = e.KeyInput.PressedDown;

//#ifdef _DEBUG
//        if(keyStates_[KEY_ESCAPE])
//            exit(0);
//#endif
    }
    return processed;

}

bool KeysHandling::IsKeyPressed( irr::EKEY_CODE keyCode )
{
    return keyStates_[keyCode];
}