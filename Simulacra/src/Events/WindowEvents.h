#pragma once

#include "Event.h"

namespace Simulacra
{
    enum class WindowEventType
    {
        WINDOW_CLOSED,
    };

    // NOTE(Edmund): Might need to revise this later
    class WindowCloseEvent : public Event<WindowEventType>
    {
    public:
        explicit WindowCloseEvent()
            : Event<WindowEventType>(WindowEventType::WINDOW_CLOSED, "Window Closed") {}
        virtual ~WindowCloseEvent() = default;
    };

}