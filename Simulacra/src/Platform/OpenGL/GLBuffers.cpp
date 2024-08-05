#include "GLBuffers.h"

#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Simulacra
{
    VertexArrayBuffer CreateVertexArrayBuffer()
    {
        VertexArrayBuffer va;
        glGenVertexArrays(1, &va.RendererID);
        glBindVertexArray(va.RendererID);

        return va;
    }

    void BindVertexArrayBuffer(uint32_t buffer)
    {
        glBindVertexArray(buffer);
    }

    VertexBuffer CreateVertexBuffer()
    {
        VertexBuffer vbo;

        glGenBuffers(1, &vbo.RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.RendererID);

        return vbo;
    }

    void BindVertexBuffer(uint32_t buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }
    
    void BufferVertexBuffer(size_t size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    void BufferVertexBuffer(size_t size, const void *data)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void BufferSubVertexBuffer(uint32_t offset, size_t size, const void *data)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    ElementBuffer CreateElementBuffer()
    {
        ElementBuffer ebo;

        glGenBuffers(1, &ebo.RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.RendererID);

        return ebo;
    }

    void BindElementBuffer(uint32_t buffer)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    }

    void BufferElementBuffer(size_t size)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    }

    void BufferElementBuffer(size_t size, const void *data)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void SetVertexAttribute(uint32_t index, int size, int stride, void* pointer)
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
        glEnableVertexAttribArray(index);
    }
}
