#include "Buffers.h"

#include <glad/glad.h>

namespace Simulacra
{
    VertexArrayBuffer CreateVertexArrayBuffer()
    {
        VertexArrayBuffer va;
        glCreateVertexArrays(1, &va.RendererID);
        glBindVertexArray(GL_VERTEX_ARRAY);

        return va;
    }
}
