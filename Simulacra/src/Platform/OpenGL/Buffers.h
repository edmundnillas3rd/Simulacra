#pragma once

#include <cstdint>

namespace Simulacra
{
    struct VertexArrayBuffer
    {
        uint32_t RendererID;
    };


    struct ElementBufferObject
    {
        uint32_t RendererID;
    };

    VertexArrayBuffer CreateVertexArrayBuffer();
    void BindVertexArrayBuffer(uint32_t buffer);
    void BufferArrayBuffer(size_t size, void* data);

    ElementBufferObject CreateElementBuferObject();
    void BindElementBufferObject(uint32_t buffer);
    void BufferElementData(size_t size, void* data);

    void SetVertexAttribute(uint32_t index, int size, int stride, void* pointer);
}
