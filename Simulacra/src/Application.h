
#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Events/WindowEvents.h"

namespace Simulacra
{
    struct Window
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
    };

    struct Application
    {
        Window Props;
        bool Running;
    };

    void OnEventExitApplication(const Event<WindowEventType>& event);

    Application* CreateApplication();
}