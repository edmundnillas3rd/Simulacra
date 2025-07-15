#include "Window.h"

#include "../Platform/SDL/SDLWindow.h"

// TODO(Edmund): must implement platform dependent code in the future
namespace Simulacra
{
    void StartWindowSubsystem(const WindowProps& props)
    {
        CreatePlatformWindow(props);
    }

    void ShutdownWindowSubsystem()
    {
        DestroyPlatformWindow();
    }

    void PollWindowEvents()
    {
        SDLPollWindowEvents();
    }

    void UpdateWindow()
    {
        SDLUpdateWindow();
    }

    void MakeContextCurrent()
    {
        SDLGLMakeContextCurrent();
    }

    void ImGuiBeginRender()
    {
        SDLImGuiBeginRender();
    }

    void ImGuiEndRender()
    {
        SDLImGuiEndRender();
    }
}