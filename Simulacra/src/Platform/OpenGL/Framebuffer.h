#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Framebuffer
    {
        GLuint ID;
        GLuint ColorBuffer;
        GLuint RenderBuffer;
    };

    Framebuffer CreateFramebuffer();
    void BindFramebuffer(GLuint id);
    void UnBindFramebuffer();
}