#pragma once

#include <string>
#include <functional>

#include "src/Event.h"

namespace Simulacra
{
    using CallbackFn = std::function<void(Event)>;

    struct Window
    {
        enum class Platform
        {
            NONE    = -1,
            WINDOWS = 0,
            LINUX   = 1,
            DARWIN  = 2
        };

        Platform platform;

        std::string title;
        uint32_t width;
        uint32_t height;
        CallbackFn callback;
    };

    Window CreateWindow(const std::string& title, uint32_t width, uint32_t height, CallbackFn callback);
    bool StartWindow(const char* path, Window window);
    void PollWindowEvents(Window window);
    void ClearWindowBuffer(Window window);
    void ShutdownWindow(Window window);
}
