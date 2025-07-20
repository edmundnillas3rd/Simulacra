#include "../GraphicsContext.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "../PlatformUtils.h"
#include "../GraphicsContext.h"
#include "spch.h"

namespace Simulacra
{
    void* CreateGraphicsContext(void* window)
    {
        SDL_Window* currentWindow = static_cast<SDL_Window*>(window);
        SDL_GLContext context = SDL_GL_CreateContext(currentWindow);

        SIMULACRA_ASSERT(context != nullptr, "Failed to create opengl context");

        return context;
    }

    void MakeContextCurrent(void* window, GraphicsContext context)
    {
        SDL_GL_MakeCurrent(static_cast<SDL_Window*>(window), context);
    }
}