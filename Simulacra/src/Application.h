#pragma once
#include <string>

namespace Simulacra 
{
    struct Application
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
    };

    void CreateApplication(const std::string& title = "", uint32_t width = 0, uint32_t height = 0);
    void RunApplication();
}