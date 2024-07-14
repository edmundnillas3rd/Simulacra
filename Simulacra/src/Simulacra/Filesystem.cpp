#include "Filesystem.h"

#include <filesystem>

namespace Simulacra
{
    FileSystem FileManager;

    void InitializePlatformFilesystem(Window window)
    {
    #ifdef _WIN32
        if (!window.Path.empty())
        {
            std::filesystem::current_path(std::filesystem::path(window.Path));
            FileManager.CurrenWorkingDirectory = std::filesystem::current_path().string() + "\\";
            std::cout << FileManager.CurrenWorkingDirectory << std::endl;
        }
    #endif
    }
}