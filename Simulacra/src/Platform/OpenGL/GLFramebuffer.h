#pragma once
#include <string>

#include "GLTexture.h"
#include "GLBuffers.h"

namespace Simulacra
{
    struct Framebuffer
    {
        uint32_t ID;
        std::string Name;
        Texture TextureBuffer;
        VertexArrayBuffer FramebufferVAO;
    };

    Framebuffer CreateFramebuffer(const std::string& name);
    void BindFramebuffer(uint32_t id);
    void SetViewport(uint32_t width, uint32_t height);

    Texture CreateTextureAttachment(uint32_t width, uint32_t height);

}