#pragma once
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include "src/Event.h"

namespace Simulacra
{
    bool InitializeSDL(const std::string& title, const uint32_t width, const uint32_t height);
    void PollSDLEvents(const std::function<void(Event)>& fn);
    void ClearSDLWindowBuffer();
    void ShutdownSDL();
}