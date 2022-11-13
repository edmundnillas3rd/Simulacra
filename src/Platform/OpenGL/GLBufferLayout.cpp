#include "GLBufferLayout.h"

#include "GLDebug.h"

GLuint CreateBufferLayout()
{
    GLuint VAO;

    glGenVertexArrays(1, &VAO);
    glCheckError();

    return VAO;
}

void BindBufferLayout(GLuint VAO)
{
    glBindVertexArray(VAO);
    glCheckError();
}

void SetBufferLayout(GLuint index, GLint size, GLsizei stride, void* pointer)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glCheckError();
}

void EnableVAByIndex(GLuint index)
{
    glEnableVertexAttribArray(index);
    glCheckError();
}