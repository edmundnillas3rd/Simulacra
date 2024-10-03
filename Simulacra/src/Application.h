#pragma once
#include <string>

namespace Simulacra 
{
    void CreateApplication(const std::string& title = "Untitled", uint32_t width = 1366, uint32_t height = 768);
    void RunApplication();
}