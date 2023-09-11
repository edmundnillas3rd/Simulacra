#pragma once
#include "Event.h"

namespace Simulacra
{
    class Layer
    {
    public:
        Layer()             = default;
        virtual ~Layer()    = default;

        virtual void OnUpdate(float deltaTime) {};
        virtual void OnEvent(Event event) {};
        virtual void OnImGuiRender() {};
    };
}
