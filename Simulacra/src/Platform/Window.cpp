#include "Window.h"

namespace Simulacra
{
    extern void CreatePlatformWindow(const std::string& title, uint32_t width, uint32_t height, const std::function<void(Event)>& eventCallbackfn);
    extern void DestroyPlatformWindow();

    void StartWindowSubsystem(const WindowProps& props)
    {
        CreatePlatformWindow(props.Title, props.Width, props.Height, props.EventCallbackfn);
    }

    void ShutdownWindowSubsystem()
    {
        DestroyPlatformWindow();
    }
}