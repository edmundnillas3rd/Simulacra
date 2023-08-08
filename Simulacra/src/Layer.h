#pragma once
#include "Event.h"

namespace Simulacra
{
    class Layer
    {
    public:
        Layer()             = default;
        virtual ~Layer()    = default;

        virtual void OnStart() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(Event event) {};
        virtual void OnRender() {};
        virtual void OnEnd() {};
    };
}