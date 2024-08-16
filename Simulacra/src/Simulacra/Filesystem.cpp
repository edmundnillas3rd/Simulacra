#include "Filesystem.h"

#include <filesystem>

namespace Simulacra
{
    FileSystem FileManager;

    void InitializeFilesystem(Window window)
    {
    #ifdef _WIN32
        if (!window.Path.empty())
        {
            std::filesystem::current_path(std::filesystem::path(window.Path));
            FileManager.CurrenWorkingDirectory = std::filesystem::current_path().make_preferred().string().append("\\");
            std::cout << FileManager.CurrenWorkingDirectory << std::endl;
        }
    #endif
    }

    std::string FormatFilepathPlatform(const std::string& path)
    {
        std::filesystem::path p = path;
        std::filesystem::path cw = FileManager.CurrenWorkingDirectory;
        return cw.string().append(p.make_preferred().string());
    }
}