#include "Window.h"

#include "Platform/SDL2/SDL2.h"

namespace Simulacra
{
    Window CreateWindow(const std::string& title, uint32_t width, uint32_t height, CallbackFn callback)
    {
        Window window;

    #if _WIN32
        window.platform = Window::Platform::WINDOWS;
    #elif __linux__
        window.platform = Window::Platform::LINUX;
    #else
        #error Platform not supported
    #endif

        window.title = title;
        window.width = width;
        window.height = height;
        window.callback = callback;

        return window;
    }

    bool StartWindow(Window window)
    {
        bool success = false;
        switch (window.platform)
        {
        case Window::Platform::LINUX:
            success = InitializeSDL(window.title.c_str(), window.width, window.height);
            break;
        default:
            success = false;
            break;
        }

        return success;
    }

    void PollWindowEvents(Window window)
    {
        switch (window.platform)
        {
        case Window::Platform::LINUX:
            PollSDLEvents(window.callback);
            break;
        default:
            break;
        }
    }

    void ClearWindowBuffer(Window window)
    {
        switch (window.platform)
        {
        case Window::Platform::LINUX:
            ClearSDLWindowBuffer();
            break;
        default:
            break;
        }
    }

    void ShutdownWindow(Window window)
    {
        switch (window.platform)
        {
        case Window::Platform::LINUX:
            ShutdownSDL();
            break;
        default:
            break;
        }
    }
}
