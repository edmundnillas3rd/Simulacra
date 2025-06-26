#pragma once

#include <string>
#include <vector>
#include <functional>

#include "../Events/Event.h"

namespace Simulacra 
{
    class Application
    {
    public:
        bool CreateApplication(const std::string& title, uint32_t width, uint32_t height);
        void RunApplication();

        virtual void OnStart() {};
        virtual void OnUpdate(float delta) {};
    private:
        void StartApplicationSubsystems();
        void ShutdownApplicationSubsystems();

        void WindowCallbackfn(Event event);

    private:
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        bool Running;
    };
}