#pragma once
#include <string>

#include "GLTexture.h"
#include "GLBuffers.h"

namespace Simulacra
{
    struct Framebuffer
    {
        uint32_t ID;
        Texture AttachColorTexture;
    };

    Framebuffer CreateFramebuffer(uint32_t width, uint32_t height);
    void BindFramebuffer(const Framebuffer& framebuffer);
    void UnbindFramebuffer();
    void WriteFramebuffer(const Framebuffer& framebuffer);
    void ReadFramebuffer(const Framebuffer& framebuffer);
    void WriteToDefaultFramebuffer();
    void ReadToDefaultFramebufferFramebuffer();
    void SetViewport(uint32_t width, uint32_t height);
    void BlitFramebuffer(const Framebuffer& srcFramebuffer, const Framebuffer& destFramebuffer);
    void BlitFramebuffer(const Framebuffer &srcFramebuffer, uint32_t width, uint32_t height);

    void SetColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
    void Clear();

    Texture CreateTextureAttachment(uint32_t width, uint32_t height);

}