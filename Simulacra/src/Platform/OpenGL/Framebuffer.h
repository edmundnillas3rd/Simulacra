#pragma once
#include <string>

#include "Texture.h"

namespace Simulacra
{
    struct Framebuffer
    {
        uint32_t ID;
        std::string Name;
    };

    Framebuffer CreateFramebuffer(const std::string& name);
    Texture CreateTextureAttachment();
    void BindFramebuffer(uint32_t id);
}