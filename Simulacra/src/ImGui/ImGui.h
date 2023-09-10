#pragma once

#include <SDL.h>
#include "src/Event.h"

namespace Simulacra
{
    void ImGuiOnAttach();
    void ImGuiOnDetach();
    void ImGuiEvent(SDL_Event event);
    void ImGuiBegin();
    void ImGuiEnd();
}