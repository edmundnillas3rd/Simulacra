#include "Window.h"

#include <iostream>

#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Platform/OpenGL/OpenGL.h"

static SDL_Window* window = nullptr;

static std::function<void(void)> windowEventCallbackfn = nullptr;

void StartWindow()
{
    SDL_Init(SDL_INIT_VIDEO);

    InitializeOpenGL();
    
    const uint32_t SCREEN_WIDTH = 960, SCREEN_HEIGHT = 640;
    int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    window = SDL_CreateWindow("Simulacra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

    CreateGLContext(window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    std::cout << "OpenGL loaded" << std::endl;
    std::cout << "Vendor:   " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version:  " << glGetString(GL_VERSION) << std::endl;

    SDL_GL_SetSwapInterval(1);

    int w,h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
}

void BindWindowEvent(const std::function<void(void)>& func)
{
    windowEventCallbackfn = func;
}

void UpdateWindow()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            windowEventCallbackfn();
            break;
        }
    }
}

void RenderWindow()
{
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
}

void ShutdownWindow()
{
    DestroyGLContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
