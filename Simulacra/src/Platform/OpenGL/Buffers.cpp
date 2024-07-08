#include "Buffers.h"

#include <glad/glad.h>

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
}
