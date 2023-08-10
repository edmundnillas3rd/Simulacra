#pragma once

#include "Layer.h"

namespace Simulacra
{
    struct ApplicationArgs
    {
        std::string name;
    };
    

    class Application
    {
    public:
        Application(ApplicationArgs args)
            : m_Args(args)
        {

        }
        
        virtual ~Application() = default;

        ApplicationArgs GetApplicationArgs() { return m_Args; }

    private:
        ApplicationArgs m_Args;
    };
    
    void RunApplication(const char* title);

    void PushLayer(Layer* layer);
    void PopLayer();
}