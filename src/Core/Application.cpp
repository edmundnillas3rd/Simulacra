#include "Application.h"
#include "Platform/Windows/Window.h"

static bool running = true;

static void OnCloseEvent()
{
    running = false;
}

void RunApplication()
{
    StartWindow();
    BindWindowEvent(OnCloseEvent);

    while (running)
    {
        UpdateWindow();
        RenderWindow();
    }

    ShutdownWindow();
}
