
#pragma once

#include <functional>
#include <string>
#include <vector>

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

    Application* CreateApplication();
}