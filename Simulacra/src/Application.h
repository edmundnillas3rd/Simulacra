
#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Events/WindowEvents.h"
#include "src/Window.h"

namespace Simulacra
{

    struct Application
    {
        Window Props;
        bool Running;

        virtual void OnUpdate(float deltaTime) {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent() {};
    };
    
    void AddLayer(Application* layer);
    Application* CreateApplication();
}