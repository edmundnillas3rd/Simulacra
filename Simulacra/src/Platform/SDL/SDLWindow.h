#pragma once
#include "../../Core/Window.h"

namespace Simulacra
{
    void CreatePlatformWindow(const WindowProps& props);
    void DestroyPlatformWindow();

    void SDLPollWindowEvents();
    void SDLUpdateWindow();

    void SDLImGuiBeginRender();
    void SDLImGuiEndRender();
}