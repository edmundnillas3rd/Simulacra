#include "Window.h"

namespace Simulacra
{
    void StartWindowSubsystem(const WindowProps& props)
    {
        CreatePlatformWindow(props.Title.c_str(), props.Width, props.Height);
    }

}