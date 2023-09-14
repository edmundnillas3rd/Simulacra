#pragma once

#include <SDL.h>

namespace Simulacra
{
    enum class EventType
    {
        SIMULACRA_NONE          = -1,
        SIMULACRA_EXIT          = 0,
        SIMULACRA_WINDOW_EVENT  = 1,
        SIMULACRA_WINDOW_RESIZE_EVENT  = 2

    };

    struct Event
    {
        std::string Name;
        EventType Type;
        SDL_Event APIEvent;
    };
}