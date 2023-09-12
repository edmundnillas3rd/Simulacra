#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Framebuffer
    {
        GLuint ID;
    };

    Framebuffer CreateFramebuffer();
    void AttackTextureToFramebuffer(GLuint buffer);
}