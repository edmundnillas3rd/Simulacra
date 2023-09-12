#include "Texture.h"

#include "src/Core/Window.h"

namespace Simulacra
{
    Texture CreateTexture()
    {
        Texture texture;
        
        GLuint renderedTexture;
        glGenTextures(1, &renderedTexture);

        glBindTexture(GL_TEXTURE_2D, renderedTexture);

        Window props = GetWindowSize();

        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, props.width, props.height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        texture.ID = renderedTexture;

        return texture;
    }
}
