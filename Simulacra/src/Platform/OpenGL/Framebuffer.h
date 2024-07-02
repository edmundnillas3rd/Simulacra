#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Framebuffer
    {
        GLuint FBO;
    };

    Framebuffer CreateFramebuffer();
    void BindFramebuffer(GLuint buffer = 0);
    void DeleteFramebuffer(GLuint buffer);
}