#pragma once

namespace Simulacra
{
    using GraphicsContext = void*;

    void* CreateGraphicsContext(void* window);
    void MakeContextCurrent(void* window, GraphicsContext context);
}