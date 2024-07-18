#include "GLRenderer.h"

#include <glad/glad.h>


namespace Simulacra
{
    void DrawIndices(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

}

