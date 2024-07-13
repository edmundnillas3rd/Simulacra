#pragma once

#include "Event.h"

namespace Simulacra
{

    // NOTE(Edmund): Might need to revise this later
    class WindowCloseEvent : public Event
    {
    public:
        explicit WindowCloseEvent()
            : Event(EventType::WINDOW_CLOSED, "Window Closed")
        {
        }
        virtual ~WindowCloseEvent() = default;

        static EventType StaticType()
        {
           return EventType::WINDOW_CLOSED;
        }

        virtual EventType Type() const override
        {
            return StaticType();
        }


    };

    class WindowResizeEvent : public Event
    {
    public:
        explicit WindowResizeEvent(uint32_t w, uint32_t h)
            : Event(EventType::WINDOW_RESIZED, "Window Resized")
        {
            Width = w;
            Height = h;
        }
        virtual ~WindowResizeEvent() = default;

        static EventType StaticType()
        {
           return EventType::WINDOW_RESIZED;
        }

        virtual EventType Type() const override
        {
            return StaticType();
        }

        uint32_t Width;
        uint32_t Height;

    };

}