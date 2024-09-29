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

    void CreateApplication(const std::string& title, uint32_t width, uint32_t height);
    void RunApplication();
}