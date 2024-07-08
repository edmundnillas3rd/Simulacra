#include "Input.h"
#include <SDL.h>

namespace Simulacra
{
    bool IsKeyPressed(VKEY key)
    {
        const Uint8* input = SDL_GetKeyboardState(nullptr);


        return (bool)input[(int)key] == 1;
    }
}