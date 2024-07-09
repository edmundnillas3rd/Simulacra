#include "src/Simulacra/Time.h"

#include <SDL.h>

namespace Simulacra
{
    float CurrentTime()
    {
        return (float)SDL_GetTicks64();
    }
}
