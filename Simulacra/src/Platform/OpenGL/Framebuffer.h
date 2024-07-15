#pragma once
#include <string>

#include "Texture.h"
#include "Buffers.h"

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

    Texture CreateTextureAttachment();

}