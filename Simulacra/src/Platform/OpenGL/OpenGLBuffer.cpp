#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Simulacra
{
    Buffer CreateBuffer()
    {
        Buffer buffer = {};

        glGenBuffers(1, &buffer.BufferID);

        return buffer;
    }

    Buffer CreateVertexArray()
    {
        Buffer buffer = {};

        glGenVertexArrays(1, &buffer.BufferID);

        return buffer;
    }

    void BindBuffer(const Buffer& buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer.BufferID);
    }

    void BindVertexArray(const Buffer& buffer)
    {
        glBindVertexArray(buffer.BufferID);
    }

    void AllocateSizeBuffer(size_t size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    void WriteData(uint32_t offset, size_t size, const void* data)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void ReadData(uint32_t offset, size_t size, void *data)
    {
        glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void SetVertexAttrib(uint32_t index, size_t size, size_t stride, const void* pointer)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    }
}