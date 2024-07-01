
#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Events/WindowEvents.h"
#include "src/Window.h"

namespace Simulacra
{
    struct Application
    {
        Window Props;
        bool Running;
    };
    
    Application* CreateApplication();
}