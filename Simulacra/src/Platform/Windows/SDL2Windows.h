#pragma once

#include "src/Events/WindowEvents.h"
#include "src/Simulacra/Window.h"

namespace Simulacra
{
    bool InitializePlatformWindow(Window window);
    bool ShutdownPlatformWindow();
    void PollEvents();
    void PlatformRender(Window window);
}
