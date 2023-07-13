#include "GLBuffer.h"

#include "GLDebug.h"

GLuint CreateIndexBuffer()
{
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glCheckError();
    return EBO;
}

void SetIndexBuffer(void* data, GLsizeiptr size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glCheckError();
}

void BindIndexBuffer(GLuint EBO)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glCheckError();
}
