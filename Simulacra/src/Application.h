
#pragma once

#include <functional>
#include <string>

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
        Window props;
    };

    Application* CreateApplication();
}