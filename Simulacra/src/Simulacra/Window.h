#pragma once 

#include <string>
#include <cstdint>
#include <functional>

#include "src/Events/Event.h"

namespace Simulacra
{
    struct Window
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        std::string Path;
    };

    using CallbackFn = std::function<void(Event&)>;

    void SubmitApplicationCallback(const CallbackFn& fn);
    bool InitializePlatformWindow(Window window);
    bool ShutdownPlatformWindow();
    void PollEvents();
    void PlatformRender(Window window);

    void BeginImGuiRender();
    void EndImGuiRender();

    Window GetCurrentWindow();
}