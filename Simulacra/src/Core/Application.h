#pragma once

#include <string>
#include <functional>

#include "../Events/Event.h"

namespace Simulacra 
{
    class Application
    {
    public:
        struct Config
        {
            std::string                         Title;

            uint32_t                            Width;
            uint32_t                            Height;

            std::filesystem::path               WorkingDirectory;
        };
    public:
        Application() = default;
        virtual ~Application() = default;

        bool Create(const std::optional<Config>& config);
        void Run();

        virtual void OnStart() {};
        virtual void OnUpdate(float delta) {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent(Event event) {};
    private:
        void StartSubsystems();
        void ShutdownSubsystems();

        void WindowCallbackfn(Event event);

    private:
        Config m_Config;
        bool m_Running;
        bool m_Minimize;
    };
}