#include "Buffers.h"

#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Simulacra
{
    VertexArrayBuffer CreateVertexArrayBuffer()
    {
        VertexArrayBuffer va;
        glCreateVertexArrays(1, &va.RendererID);
        glBindVertexArray(va.RendererID);

        return va;
    }


    void BindVertexArrayBuffer(uint32_t buffer)
    {
        glBindVertexArray(buffer);
    }

    void BufferArrayBuffer(size_t size, void *data)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    ElementBufferObject CreateElementBuferObject()
    {
        ElementBufferObject ebo;

        glCreateBuffers(GL_ELEMENT_ARRAY_BUFFER, &ebo.RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.RendererID);

        return ebo;
    }

    void BindElementBufferObject(uint32_t buffer)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    }

    void BufferElementData(size_t size, void *data)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void SetVertexAttribute(uint32_t index, int size, int stride, void* pointer)
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
        glEnableVertexAttribArray(index);
    }
}
