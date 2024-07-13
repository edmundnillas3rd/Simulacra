#pragma once

#include "Event.h"

namespace Simulacra
{
    enum class WindowEventType
    {
        WINDOW_CLOSED,
        WINDOW_RESIZED
    };

    // NOTE(Edmund): Might need to revise this later
    class WindowCloseEvent : public Event<WindowEventType>
    {
    public:
        explicit WindowCloseEvent()
            : Event<WindowEventType>(WindowEventType::WINDOW_CLOSED, "Window Closed") 
        {
            // NOTE(Edmund): To be replaced with a proper logger
            std::cout << "Window is closed" << std::endl;
        }
        virtual ~WindowCloseEvent() = default;
    };

    class WindowResizeEvent : public Event<WindowEventType>
    {
    public:
        explicit WindowResizeEvent(size_t w, size_t h)
            : Event<WindowEventType>(WindowEventType::WINDOW_RESIZED, "Window Resized") 
        {
            std::cout << "Window is resize" << std::endl;
            Width = w;
            Height = h;
        }

        size_t Width;
        size_t Height;

        virtual ~WindowResizeEvent() = default;
    };

}