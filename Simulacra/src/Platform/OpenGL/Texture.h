#pragma once

#include <string>
#include <iostream>

#include <glm/glm.hpp>

#include "Buffers.h"

namespace Simulacra
{
    struct Texture
    {
        uint32_t TextureID;
        glm::ivec2 Size;
    };

    Texture LoadTexture(const std::string& path);
    void SetActiveTexture(uint32_t index);
    void BindTexture(uint32_t texture = 0);
}