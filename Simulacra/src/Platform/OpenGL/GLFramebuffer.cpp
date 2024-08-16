#include "GLFramebuffer.h"
#include <iostream>

#include <glad/glad.h>

namespace Simulacra
{
    Framebuffer CreateFramebuffer(uint32_t width, uint32_t height)
    {
        Framebuffer fbo;
        
        glGenFramebuffers(1, &fbo.ID);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo.ID);

        fbo.AttachColorTexture = CreateTextureAttachment(width, height);

        return fbo;
    }

    void BindFramebuffer(const Framebuffer& framebuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.ID);
    }

    void UnbindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void WriteFramebuffer(const Framebuffer &framebuffer)
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer.ID);
    }

    void ReadFramebuffer(const Framebuffer &framebuffer)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer.ID);
    }

    void WriteToDefaultFramebuffer()
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    void ReadToDefaultFramebufferFramebuffer()
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    }

    void SetViewport(uint32_t width, uint32_t height)
    {
        glViewport(0, 0, width, height);
    }

    void BlitFramebuffer(const Framebuffer &srcFramebuffer, const Framebuffer &destFramebuffer)
    {
        glBlitFramebuffer(0, 0, srcFramebuffer.AttachColorTexture.Width, srcFramebuffer.AttachColorTexture.Height, 0, 0, destFramebuffer.AttachColorTexture.Width, destFramebuffer.AttachColorTexture.Height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }

    void BlitFramebuffer(const Framebuffer &srcFramebuffer, uint32_t width, uint32_t height)
    {
        glBlitFramebuffer(0, 0, srcFramebuffer.AttachColorTexture.Width, srcFramebuffer.AttachColorTexture.Height, 0, 0, width, height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }

    void SetColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
    {
        glClearColor(r, g, b, a);
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Texture CreateTextureAttachment(uint32_t width, uint32_t height)
    {
        Texture texture;
        glGenTextures(1, &texture.TextureID);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.TextureID, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "FRAMEBUFFER IS NOT COMPLETE" << std::endl;
        }

        texture.Width = width;
        texture.Height = height;
        return texture;
    }
}
