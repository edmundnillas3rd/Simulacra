#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Texture
    {
        GLuint ID;
        uint32_t Width;
        uint32_t Height;
    };

    Texture LoadTexture(const std::string& path);
}
