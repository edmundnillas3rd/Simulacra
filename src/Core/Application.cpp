#include "Application.h"

#include <vector>
#include <memory>

#include "Platform/Windows/Window.h"

static bool running = true;

extern Simulacra* CreateApplication();
Simulacra* app = nullptr;

static void OnCloseEvent()
{
    running = false;
}

void RunApplication()
{
    StartWindow();
    BindWindowEvent(OnCloseEvent);

    app = CreateApplication();

    while (running)
    {
        UpdateWindow();
        app->OnEvent();
        RenderWindow();
        app->OnUpdate(0.1f);
    }

    delete app;

    ShutdownWindow();
}