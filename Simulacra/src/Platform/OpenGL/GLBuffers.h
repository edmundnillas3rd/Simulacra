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
    };

    struct VertexArrayBuffer
    {
        uint32_t RendererID;
    };

    struct UniformBuffer
    {
        uint32_t RendererID;
    };


    VertexBuffer CreateVertexBuffer();
    void BindVertexBuffer(uint32_t buffer);
    void BufferVertexBuffer(size_t size);
    void BufferVertexBuffer(size_t size, const void* data);
    void BufferSubVertexBuffer(uint32_t offset, size_t size, const void *data);

;
    ElementBuffer CreateElementBuffer();
    void BindElementBuffer(uint32_t buffer);
    void BufferElementBuffer(size_t size);
    void BufferElementBuffer(size_t size, const void* data);

    VertexArrayBuffer CreateVertexArrayBuffer();
    void BindVertexArrayBuffer(uint32_t buffer);

    void SetVertexAttribute(uint32_t index, int size, int stride, void* pointer);

    UniformBuffer CreateUniformBuffer(uint32_t size, uint32_t binding);
    void BufferUniformBuffer(uint32_t buffer, uint32_t offset, uint32_t size, const void *data);
}
