#pragma once

namespace Simulacra
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
    };


    void StartWindowSubsystem(const WindowProps& props);
    void ShutdownWindowSubsystem();

    // NOTE(Edmund): Interface for platform implementation
    void CreatePlatformWindow(const char* title, uint32_t width, uint32_t height);
    void DestroyPlatformWindow();
}