#include "GLBuffer.h"

#include "GLDebug.h"

uint32_t CreateBuffer()
{
    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glCheckError();
    return VBO;
}

void SetBuffer(void* data, GLsizeiptr size)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glCheckError();
}

void BindBuffer(GLuint VBO)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();
}
