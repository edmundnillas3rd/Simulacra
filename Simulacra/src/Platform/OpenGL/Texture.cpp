#include "Texture.h"

#include <stb_image.h>

namespace Simulacra
{
    Texture LoadTexture(const std::string& path)
    {
        Texture texture;

        int n = 0;
        int forceChannels = 4;
        unsigned char* image_data = stbi_load(path.c_str(), &texture.Texels.x, &texture.Texels.y, &n, forceChannels);
        if (!image_data)
        {
            std::cout << "Error: Could not load " + path << std::endl;
        }

        stbi_set_flip_vertically_on_load(1);

        glCreateBuffers(1, &texture.Data);
        glActiveTexture(GL_TEXTURE0);
        BindTexture(texture.Data);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Texels.x, texture.Texels.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }

    void BindTexture(GLuint texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}