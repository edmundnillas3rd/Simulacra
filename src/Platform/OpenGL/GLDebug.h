#pragma once

#include <glad/glad.h>

#define glCheckError() glCheckError_(__FILE__, __LINE__)
GLenum glCheckError_(const char *file, int line);