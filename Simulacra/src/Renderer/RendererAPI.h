#pragma once
#include <cstdint>

namespace Simulacra
{
    enum class RendererEngine
    {
        NONE            = -1,
        OPENGL          =  0,
    };

    void StartRendererSubsystem(RendererEngine engine);
    void ShutdownRendererSubsystem();
}