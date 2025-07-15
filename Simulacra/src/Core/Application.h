#pragma once

#include <string>
#include <functional>

#include "../Events/Event.h"

namespace Simulacra 
{
    class Application
    {
    public:
        struct ApplicationConfig
        {
            std::string                         Title;

            uint32_t                            Width;
            uint32_t                            Height;

            std::filesystem::path               WorkingDirectory;
        };
    public:
        Application() = default;
        virtual ~Application() = default;

        bool CreateApplication(const ApplicationConfig& props);
        void RunApplication();

        virtual void OnStart() {};
        virtual void OnUpdate(float delta) {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent(Event event) {};
    private:
        void StartApplicationSubsystems();
        void ShutdownApplicationSubsystems();

        void WindowCallbackfn(Event event);

    private:
        ApplicationConfig m_Props;
        bool m_Running;
    };
}