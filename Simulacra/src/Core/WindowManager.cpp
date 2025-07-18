#include "WindowManager.h"

#include "../Platform/SDL/SDLWindow.h"

// TODO(Edmund): must implement platform dependent code in the future
namespace Simulacra
{
    void StartWindowSubsystem(const WindowProps& props)
    {
        CreatePlatformWindow(props.Title, props.Width, props.Height, props.EventCallbackfn);
    }

    void ShutdownWindowSubsystem()
    {
        DestroyPlatformWindow();
    }
}