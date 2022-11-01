#pragma once

#include <cstdint>

#include <glad/glad.h>

struct Buffer
{
    uint32_t VBO;
};

uint32_t CreateBuffer();
void SetBuffer(void* data, GLsizeiptr size);
void BindBuffer(GLuint VBO);