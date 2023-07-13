#pragma once

#include <cstdint>Index

#include <glad/glad.h>

struct Buffer
{
    GLuint EBO;
};

GLuint CreateIndexBuffer();
void SetIndexBuffer(void* data, GLsizeiptr GLuintsize);
void BindIndexBuffer(GLuint EBO);