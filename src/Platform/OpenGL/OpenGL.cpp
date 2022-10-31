#include "OpenGL.h"

#include <SDL.h>
#include <SDL_opengl.h>

static SDL_GLContext context;

void InitializeOpenGL()
{
    SDL_GL_LoadLibrary(nullptr);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void CreateGLContext(void* window)
{
    context = SDL_GL_CreateContext(static_cast<SDL_Window*>(window));
}

void DestroyGLContext()
{
    SDL_GL_DeleteContext(context);
}
