#pragma once

#include <string>
#include <iostream>

#include <glm/glm.hpp>

#include "GLBuffers.h"

namespace Simulacra
{
    struct Texture
    {
        uint32_t TextureID;
        glm::ivec2 Size;
    };

    Texture LoadTexture(const std::string& path);
    void BindTexture(uint32_t texture = 0);

    void SetActiveTexture(uint32_t index);
}