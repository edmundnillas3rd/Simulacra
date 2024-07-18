#pragma once

#include <cstdint>

namespace Simulacra
{
    struct VertexBuffer
    {
        uint32_t RendererID;
    };

    struct ElementBuffer
    {
        uint32_t RendererID;
        uint32_t IndexCount;
    };

    struct VertexArrayBuffer
    {
        uint32_t RendererID;
    };


    VertexBuffer CreateVertexBuffer();
    void BindVertexBuffer(uint32_t buffer);
    void BufferVertexBuffer(size_t size, const void* data);
    void BufferSubVertexBuffer(uint32_t offset, size_t size, const void *data);

;
    ElementBuffer CreateElementBuffer(uint32_t count);
    void BindElementBuffer(uint32_t buffer);
    void BufferElementBuffer(size_t size, const void* data);

    VertexArrayBuffer CreateVertexArrayBuffer();
    void BindVertexArrayBuffer(uint32_t buffer);

    void SetVertexAttribute(uint32_t index, int size, int stride, void* pointer);

}
