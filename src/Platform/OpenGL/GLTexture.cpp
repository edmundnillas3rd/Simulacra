#include "GLTexture.h"

#include <iostream>

#include "GLDebug.h"

uint32_t CreateTexture()
{
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glCheckError();
    return texture;
}

void LoadTexture(const std::string& path)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void BindTexture(GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glCheckError();
}

void SetTextureParams(GLenum pname, GLint param)
{
    glTexParameteri(GL_TEXTURE_2D, pname, param);
    glCheckError();
}