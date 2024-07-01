#pragma once

#include "spch.h"

namespace Simulacra
{
    // NOTE(Edmund): normally when implement the EventType, don't use enum classes
    // We usually use a GUIDs, but in this particular case since I'm developing in 
    // VSCode which it doesn't have the GUIDs generator feature like Visual Studio Community has

    // Reference: https://github.com/Pseudomanifold/Events
    // NOTE(Edmund): To be replace with a GUIDs
    template<typename T>
    class Event
    {
    public:
        Event() = default;
        Event(T type, const std::string& name = "") : m_Type(type), m_Name(name) {}

        inline const T Type() const 
        {
            return m_Type;
        }

        inline const std::string& GetName() const 
        { 
            return m_Name;
        }

        virtual bool IsHandled()
        {
            return m_Handled;
        }
    protected:
        T m_Type;
        std::string m_Name;
        bool m_Handled = false;
    };

    
    
    template<typename T>
    class Dispatcher 
    {
    using SlotType = std::function<void(const Event<T>&)>;
    public:

        void Subscribe(T type, const SlotType& funct)
        {
            m_Observers[type].push_back(funct);
        }

        void Post(Event<T>& event)
        {
            if(m_Observers.find(event.Type()) == m_Observers.end())
                return;

            for(auto&& observer : m_Observers.at(event.Type())) 
            {
                if(!event.IsHandled()) 
                observer(event);  
            }
        }
    private:
        std::map<T, std::vector<SlotType>> m_Observers;
    };
}