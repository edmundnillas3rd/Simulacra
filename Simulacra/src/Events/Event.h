#pragma once

#include "spch.h"

namespace Simulacra
{
    enum class EventType
    {
        WINDOW_CLOSED, WINDOW_RESIZED,
        KEY_PRESSED, KEY_RELEASED
    };
    // NOTE(Edmund): normally when implement the EventType, don't use enum classes
    // We usually use a GUIDs, but in this particular case since I'm developing in 
    // VSCode which it doesn't have the GUIDs generator feature like Visual Studio Community has

    // Reference: https://github.com/Pseudomanifold/Events
    // NOTE(Edmund): To be replace with a GUIDs
    class Event
    {
    public:
        Event() = default;
        Event(EventType type, const std::string& name = "") : m_Type(type), m_Name(name) {}

        virtual ~Event() = default;

        virtual EventType Type() const = 0;

        const std::string& GetName()
        { 
            return m_Name;
        }

        virtual bool IsHandled()
        {
            return Handled;
        }

        bool Handled;
    protected:
        EventType m_Type;
        std::string m_Name;
    };

    
    
    class Dispatcher
    {
    public:
        Dispatcher(Event& event)
            : m_Event(event)
        {

        }

        template<typename T, typename F>
        bool Post(const F& func)
        {
            if (m_Event.Type() == T::StaticType())
            {
                m_Event.Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false; 
        }
    private:
        Event& m_Event;
    };
}