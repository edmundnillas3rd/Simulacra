#pragma once

#include <cstdint>

namespace Simulacra
{
    struct VertexArrayBuffer
    {
        uint32_t RendererID;
    };

    struct VertexBuffer
    {
        uint32_t RendererID;
    };

    struct ElementBuffer
    {
        uint32_t RendererID;
    };

    VertexArrayBuffer CreateVertexArrayBuffer();
    void BindVertexArrayBuffer(uint32_t buffer);

    VertexBuffer CreateVertexBuffer();
    void BindVertexBuffer(uint32_t buffer);
    void BufferVertexBuffer(size_t size, const void* data);

;
    ElementBuffer CreateElementBuffer();
    void BindElementBuffer(uint32_t buffer);
    void BufferElementBuffer(size_t size, const void* data);

    void SetVertexAttribute(uint32_t index, int size, int stride, void* pointer);

}
