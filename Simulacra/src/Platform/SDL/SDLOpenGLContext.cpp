#include "SDLOpenGLContext.h"

#include "../PlatformUtils.h"
#include "spch.h"

namespace Simulacra
{
    void* CreateGraphicsContext(SDL_Window* window)
    {
        SDL_Window* currentWindow = static_cast<SDL_Window*>(window);
        SDL_GLContext context = SDL_GL_CreateContext(currentWindow);

        SIMULACRA_ASSERT(context != nullptr, "Failed to create opengl context");

        return context;
    }

    void MakeContextCurrent(SDL_Window* window, SDL_GLContext context)
    {
        SDL_GL_MakeCurrent(window, context);
    }
}