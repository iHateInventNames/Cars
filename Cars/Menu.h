#pragma once
#include <IEventReceiver.h>

class Menu
    : public irr::IEventReceiver
{
    volatile bool isShowing_;
public:
    Menu(void);
    void Show();

    bool OnEvent(const irr::SEvent& event);
};
