#pragma once

#include <functional>

#include "../Events/Event.h"

namespace Simulacra
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        using WindowEventCallbackfn = std::function<void(Event)>;
        
        WindowEventCallbackfn EventCallbackfn;
    };

    void StartWindowSubsystem(const WindowProps& props);
    void ShutdownWindowSubsystem();

    void PollWindowEvents();
    void UpdateWindow();
    void MakeContextCurrent();

    void ImGuiBeginRender();
    void ImGuiEndRender();
}