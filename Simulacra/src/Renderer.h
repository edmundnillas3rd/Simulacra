#pragma once

#include <vector>

#include "Platform/OpenGL/Framebuffer.h"
#include "Platform/OpenGL/Texture.h"

namespace Simulacra
{
    struct Renderer
    {
        std::vector<Framebuffer> Framebuffers;
        Framebuffer CurrentFramebuffer;
    };


    void InitializeRenderer();
    void RenderTexture(Texture texture);

    void DrawLine();
}