#pragma once

#include <cstdint>

namespace Simulacra
{
    struct VertexArrayBuffer
    {
        uint32_t RendererID;
    };


    VertexArrayBuffer CreateVertexArrayBuffer();
    void BindVertexArrayBuffer(uint32_t buffer);
}
