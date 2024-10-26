#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace Simulacra
{
    void DrawIndex(size_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}