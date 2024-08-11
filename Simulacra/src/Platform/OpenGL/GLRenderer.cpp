#include "GLRenderer.h"

#include <glad/glad.h>


namespace Simulacra
{
    void WritePixel(Texture& texture, void* data)
    {
        texture.Data = data;
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture.Width, texture.Height, GL_RGBA, GL_UNSIGNED_BYTE, texture.Data);
    }

    void DrawImageTexture(uint32_t width, uint32_t height)
    {
        glDispatchCompute((unsigned int)width, (unsigned int)height, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

    void DrawIndices(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

}

