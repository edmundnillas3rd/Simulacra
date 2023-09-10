#include "Window.h"

#if _WIN32

#elif __linux__
#include "Platform/SDL2/SDL2.h"
#include "Platform/Windows/FileSystem.h"
#endif

namespace Simulacra
{
    Window CreateWindow(const std::string& title, uint32_t width, uint32_t height, CallbackFn callback)
    {
        Window window;

        window.title = title;
        window.width = width;
        window.height = height;
        window.callback = callback;

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
