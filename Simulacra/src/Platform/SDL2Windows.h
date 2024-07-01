#pragma once

#include <SDL.h>

#include "src/Events/WindowEvents.h"
#include "src/Window.h"

namespace Simulacra
{
    bool InitializePlatformWindow(Window window);
    bool ShutdownPlatformWindow();
    void PlatformEvents();
}
