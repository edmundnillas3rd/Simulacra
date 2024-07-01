#pragma once

#include <SDL.h>

#include "src/Application.h"

namespace Simulacra
{
    bool InitializePlatformWindow(Window window);
    bool ShutdownPlatformWindow();
}
