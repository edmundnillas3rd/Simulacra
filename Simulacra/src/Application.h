#pragma once

#include "Layer.h"

namespace Simulacra
{
    void RunApplication(const char* title, uint32_t width, uint32_t height);

    void PushLayer(Layer* layer);
    void PopLayer();
}