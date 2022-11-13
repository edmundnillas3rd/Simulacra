#pragma once

#include <cstdint>

#include <glad/glad.h>

struct Buffer
{
    GLuint VBO;
};

GLuint CreateBuffer();
void SetBuffer(void* data, GLsizeiptr GLuintsize);
void BindBuffer(GLuint VBO);