#pragma once

#include <string>

namespace Simulacra
{
    struct Texture
    {
        uint32_t TextureID;
        int32_t Width, Height;
        void* Data;
    };

    Texture LoadTexture(const std::string& path);
    void BindTexture(const Texture& texture);
    void SetActiveTexture(uint32_t index = 0);
}