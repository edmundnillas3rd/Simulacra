#pragma once

#include <cinttypes>

namespace Simulacra
{
    struct Buffer
    {
        uint32_t BufferID;
    };

    Buffer CreateBuffer();
    Buffer CreateVertexArray();

    void BindBuffer(const Buffer& buffer);
    void BindIndexBuffer(const Buffer& buffer);

    void BindVertexArray(const Buffer& buffer);

    void AllocateSizeBuffer(size_t size);

    void WriteData(uint32_t offset, size_t size, const void* data);
    void WriteIndexData(size_t size, const void* data);

    void ReadData(uint32_t offset, size_t size, void* data);
    void SetVertexAttrib(uint32_t index, size_t size, size_t stride, const void* pointer);
}