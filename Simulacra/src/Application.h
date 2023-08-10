#pragma once

#include "Layer.h"

namespace Simulacra
{
    struct ApplicationArgs
    {
        std::string name;
        std::function<void()> submit;
    };

    using Application = ApplicationArgs;

    void RunApplication(Application* app);

    void PushLayer(Layer* layer);
    void PopLayer();
}