#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Window.h"
#include "src/Events/Event.h"

namespace Simulacra
{
    // TODO(Edmund): Should probably make a dedicated "command line"/"app configuration" settings
    // that would determined the entire behavior of the entire engine

    struct Application
    {
        Window Props;
        bool Running;

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(float deltaTime) {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent(Event& event) {};
    };
    
    void AddLayer(Application* layer);
    Application* CreateApplication();
    bool IsApplicationRunning();
}