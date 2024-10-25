#pragma once

#include <cstdint>

namespace Simulacra
{
    struct MouseEvent
    {
        uint32_t X; 
        uint32_t Y; 
        uint32_t Clicks;
        uint32_t Button;
    };
}