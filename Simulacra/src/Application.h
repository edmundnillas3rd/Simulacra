#pragma once

#include <string>
#include <vector>
#include <functional>

#include "Events/Event.h"

namespace Simulacra 
{
    class ApplicationLayer
    {
    public:
        ApplicationLayer() = default;
        ~ApplicationLayer() = default;

        virtual void OnStart() {}
        virtual void OnEvent(Event event) {}
        virtual void OnUpdate(float deltaTime) {}
    };

    void CreateApplication(const std::string& title = "Untitled", uint32_t width = 1366, uint32_t height = 768, const std::vector<ApplicationLayer*>& layers = {});
    void RunApplication();
}