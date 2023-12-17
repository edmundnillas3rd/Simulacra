#include "Window.h"

#if _WIN32
// #error "Windows is unsupported at this moment
#elif __linux__
#endif

#include "Platform/Linux/FileSystem.h"
#include "Platform/SDL2/SDL2.h"

namespace Simulacra
{
    static Window window;
    Window CreateWindow(const std::string& title, uint32_t width, uint32_t height, CallbackFn callback)
    {
        window.title = title;
        window.width = width;
        window.height = height;
        window.callback = callback;

        return window;
    }

    Window GetWindowSize()
    {
        SDLWindowProps props = GetWindowProps();

        window.width = props.Width;
        window.height = props.Height;

        return window;
    }

    void StartWindow(const char* path, Window window)
    {
        SetCWDPath(path);
        InitializeSDL(window.title.c_str(), window.width, window.height);
    }

    void PollWindowEvents(Window window)
    {
        PollSDLEvents(window.callback);
    }

    void ClearWindowBuffer()
    {
        ClearSDLWindowBuffer();
    }

    void ShutdownWindow()
    {
        ShutdownSDL();
    }
}
