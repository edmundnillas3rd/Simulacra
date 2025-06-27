#include "RendererAPI.h"

#include "../Platform/OpenGL/OpenGLRenderer.h"

namespace Simulacra
{
    void StartRendererSubsystem(RendererEngine engine)
    {
        switch (engine)
        {
        case RendererEngine::OPENGL:    CreateOpenGLRenderer(); break;
        case RendererEngine::NONE:                              break;
        }

    }

    void ShutdownRendererSubsystem()
    {
    }
}