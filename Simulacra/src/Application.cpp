#include <string>
#include <SDL2/SDL.h>

#include "Platform/SDL2/SDL2.h"

namespace Simulacra
{
    struct ApplicationState
    {
        bool running;
    };

    static ApplicationState s_State;

    static void StartApplication();
    static void ShutdownApplication();
    static void PollEvents();

    void RunApplication(const char* title, uint32_t width, uint32_t height)
    {
        StartApplication();
        while (s_State.running)
        {
            PollEvents();

            if (!s_State.running) break;
        }
        ShutdownApplication();
    }

    static void StartApplication()
    {
        s_State.running = true;
    }

    static void PollEvents()
    {
        
    }

    static void ShutdownApplication()
    {
        
    }
}