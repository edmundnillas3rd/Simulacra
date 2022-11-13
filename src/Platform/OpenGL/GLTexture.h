#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include <string>
#include <cstdint>


struct Texture
{
    GLuint ID;
};

GLuint CreateTexture();
void LoadTexture(const std::string& path);
void BindTexture(GLuint texture);
void SetTextureParams(GLenum pname, GLint param);