#pragma once

#include <functional>

#include "Events/Event.h"

namespace Simulacra
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
    };

    using EventCallbackfn = std::function<void(Event)>;

    void SubmitCallback(const EventCallbackfn& fn);
    void StartWindowSubsystem(const WindowProps& props);
    void ShutdownWindowSubsystem();

    // NOTE(Edmund): Interface for platform implementation
    void CreatePlatformWindow(const char* title, uint32_t width, uint32_t height);
    void PollEvents();
    void UpdateWindow();
    void DestroyPlatformWindow();

    void GetCurrentWindowSize(int& w, int& h);
}