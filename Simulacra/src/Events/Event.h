#pragma once

#include "KeyEvents.h"

#include <string>
#include <cstdint>

namespace Simulacra
{
    enum class EventType : uint32_t
    {
        WINDOW_INSTANCE_CLOSE, WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MINIMIZE,
        KEY_PRESSED_UP, KEY_PRESSED_DOWN,
        MOUSE_MOTION, MOUSE_PRESSED_DOWN, MOUSE_PRESSED_UP,
    };

    struct Event
    {
        std::string     UUID;
        EventType       Type;
        VKEY            Key;
    };
};