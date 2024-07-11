#pragma once 

#include <string>
#include <cstdint>

namespace Simulacra
{
    struct Window
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
    };

    bool InitializePlatformWindow(Window window);
    bool ShutdownPlatformWindow();
    void PollEvents();
    void PlatformRender(Window window);

    Window GetCurrentWindow();
}