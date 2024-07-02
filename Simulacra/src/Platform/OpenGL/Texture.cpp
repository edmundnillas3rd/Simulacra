#include "Texture.h"

namespace Simulacra
{
    Texture LoadTexture()
    {
        Texture texture;

        glCreateBuffers(1, &texture.Data);
        BindTexture(texture.Data);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }

    void BindTexture(GLuint texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}