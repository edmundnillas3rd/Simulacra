#pragma once

#include <cstdint>

#include <glad/glad.h>

struct BufferLayout
{
    GLuint VAO;
};

GLuint CreateBufferLayout();
void BindBufferLayout(GLuint VAO);
void SetBufferLayout(GLuint index, GLint size, GLsizei stride, void* pointer);
void BindVAO(GLuint VAO);
void EnableVAByIndex(GLuint index);