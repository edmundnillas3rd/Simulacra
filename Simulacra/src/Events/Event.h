#pragma once

#include <string>
#include <cstdint>

namespace Simulacra
{
    enum class EventType : uint32_t
    {
        WINDOW_CLOSE, WINDOW_RESIZE,
        KEY_PRESSED_UP, KEY_PRESSED_DOWN,
        MOUSE_MOTION, MOUSE_PRESSED_DOWN, MOUSE_PRESSED_UP,
    };

    struct Event
    {
        std::string UUID;
        EventType Type;
    };
};