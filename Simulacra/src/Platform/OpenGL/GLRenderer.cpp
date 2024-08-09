#include "GLRenderer.h"

#include <glad/glad.h>


namespace Simulacra
{
    void RenderComputeShader(uint32_t width, uint32_t height)
    {
        glDispatchCompute((unsigned int)width, (unsigned int)height, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

    void DrawIndices(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

}

