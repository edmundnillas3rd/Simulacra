#pragma once

#include <string>
#include <functional>

#include "../Events/Event.h"

namespace Simulacra 
{
    class Application
    {
    public:
        struct ApplicationProps
        {
            std::string Title;
            uint32_t Width;
            uint32_t Height;

        };
    public:
        Application() = default;
        virtual ~Application() = default;

        bool CreateApplication(const ApplicationProps& props);
        void RunApplication();

        virtual void OnStart() {};
        virtual void OnUpdate(float delta) {};
        virtual void OnImGuiRender() {};
    private:
        void StartApplicationSubsystems();
        void ShutdownApplicationSubsystems();

        void WindowCallbackfn(Event event);

    private:
        ApplicationProps m_Props;
        bool m_Running;
    };
}