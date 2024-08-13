#pragma once

#include <string>
#include <iostream>

#include <glm/glm.hpp>

#include "GLBuffers.h"

namespace Simulacra
{
    struct Texture
    {
        uint32_t TextureID;
        int32_t Width;
        int32_t Height;
        void* Data;
    };

    Texture LoadTexture(const std::string& path);
    Texture CreateTexture(int32_t width, int32_t height);
    Texture CreateImageTexture(int32_t width, int32_t height);
    void BindTexture(uint32_t slot, uint32_t texture);

    void SetActiveTexture(uint32_t index);
}