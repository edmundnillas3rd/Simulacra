#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Texture
    {
        GLuint Data;
    };

    Texture LoadTexture();
    void BindTexture(GLuint texture = 0);
}