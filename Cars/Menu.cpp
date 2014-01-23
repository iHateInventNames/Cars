#include "StdAfx.h"
#include "Menu.h"
#include "Device.h"
#include "KeysHandling.h"

using namespace irr;

namespace
{
    enum { GUI_ID_CONTINUE = 101, GUI_ID_EXIT };
}


Menu::Menu(void)
:isShowing_(false)
{
    
}

void Menu::Show()
{
    using namespace gui;
    using namespace scene;

    // draw overlay menu
    IrrlichtDevice* device = Device::Instance().IrrlichtDevice();
    gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

    // change event receiver
    irr::IEventReceiver* eventReceiverBackup = device->getEventReceiver();
    device->setEventReceiver(this);

    guiEnvironment->addButton(core::recti(10,10,100,30), 0, GUI_ID_CONTINUE, L"Continue");
    guiEnvironment->addButton(core::recti(10,40,100,60), 0, GUI_ID_EXIT, L"Exit");

    video::IVideoDriver* driver = Device::Instance().Driver();
    ISceneManager* sceneManager = Device::Instance().SceneManager();
    isShowing_ = true;
    do
    {
        driver->beginScene(true, true, video::SColor(255,0,0,0));
        sceneManager->drawAll();
        guiEnvironment->drawAll();
        driver->endScene();
    }while(device->run() && isShowing_);

    // return event receiver
    device->setEventReceiver(eventReceiverBackup);
}

bool Menu::OnEvent( const irr::SEvent& event )
{
    using namespace gui;
    bool processed = event.EventType == EET_GUI_EVENT && event.GUIEvent.EventType == EGET_BUTTON_CLICKED;
    if (processed)
    {
        switch (event.GUIEvent.Caller->getID())
        {
        case GUI_ID_CONTINUE:
            isShowing_ = false;
            break;
        case GUI_ID_EXIT:
            exit(0);
            break;
        default:
            break;
        }
    }
    else
    {
        KeysHandling::Instance().OnEvent(event);
    }

    return processed;
}