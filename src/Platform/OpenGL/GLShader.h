#pragma once

#include <string>

uint32_t LoadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
void UseShader(uint32_t& id);