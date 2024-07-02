#include "Framebuffer.h"

#include <iostream>

namespace Simulacra
{
    Framebuffer CreateFramebuffer()
    {
        Framebuffer buffer;

        glCreateFramebuffers(1, &buffer.FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, buffer.FBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "Successfully created a buffer" << std::endl;
        }

        return buffer;
    }

    void BindFramebuffer(GLuint buffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, buffer);
    }

    void DeleteFramebuffer(GLuint buffer)
    {
        glDeleteFramebuffers(1, &buffer);
    }
}