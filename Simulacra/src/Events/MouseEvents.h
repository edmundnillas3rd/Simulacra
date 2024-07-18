#include "Event.h"

namespace Simulacra
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(int32_t x, int32_t y)
            : X(x), Y(y), Event(EventType::MOUSE_MOVED, "Mouse Moved")
        {}

        virtual ~MouseMovedEvent() = default; 
        
        static EventType StaticType()
        {
            return EventType::MOUSE_MOVED;
        }

        std::string ToString() const override
        {
            std::string s = m_Name;
            return s;
        }

        virtual EventType Type() const override
        {
            return StaticType();
        }
        
        int32_t X;
        int32_t Y;
    };
}