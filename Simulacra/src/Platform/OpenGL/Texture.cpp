#include "Texture.h"
#include <stb_image.h>

#include "src/Core/Window.h"
#include "src/Core/Log.h"
#include "src/Platform/Linux/FileSystem.h"

namespace Simulacra
{
    Texture LoadTexture(const std::string& path)
    {
        Texture texture;
        glGenTextures(1, &texture.ID);

        int width, height, nrChannels;
        
        std::string formattedPath = filesystem.cwd + path;
        unsigned char *data = stbi_load(formattedPath.c_str(), &width, &height, &nrChannels, 0);

        texture.Width = width;
        texture.Height = height;

        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, texture.ID); 

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            SIM_LOG_ERROR("Failed to load texture");
        }
        stbi_image_free(data);
        
        return texture;
    }
}
