#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Texture
    {
        GLuint ID;
    };

    Texture CreateTexture();
}
