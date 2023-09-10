#pragma once

#include <string>
#include <functional>

#include "src/Event.h"

namespace Simulacra
{
    using CallbackFn = std::function<void(Event)>;

    struct Window
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        CallbackFn callback;
    };

    Window CreateWindow(const std::string& title, uint32_t width, uint32_t height, CallbackFn callback);
    void StartWindow(const char* path, Window window);
    void PollWindowEvents(Window window);
    void ClearWindowBuffer();
    void ShutdownWindow();
}
