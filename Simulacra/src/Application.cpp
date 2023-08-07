#include <string>
#include <SDL2/SDL.h>

#include "Event.h"
#include "Platform/SDL2/SDL2.h"

namespace Simulacra
{
    struct ApplicationState
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool running;
    };


    static ApplicationState s_State;

    static void StartApplication();
    static void ShutdownApplication();
    static void PollEvents();

    auto callbackFn = [](Event event) {
        switch (event)
        {
        case Event::SIMULACRA_EXIT:
            s_State.running = false;
            break;
        default:
            break;
        }
    };

    void RunApplication(const char* title, uint32_t width, uint32_t height)
    {
        s_State.title = title;
        s_State.width = width;
        s_State. height = height;

        StartApplication();
        while (s_State.running)
        {
            PollEvents();
            if (!s_State.running) break;
            ClearSDLWindowBuffer();
        }
        ShutdownApplication();
    }

    static void StartApplication()
    {
        s_State.running = InitializeSDL(s_State.title, s_State.width, s_State.height);
    }

    static void PollEvents()
    {
        PollSDLEvents(callbackFn);
    }

    static void ShutdownApplication()
    {
        ShutdownSDL();
    }
}