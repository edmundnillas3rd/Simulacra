#include "../../Core/FileManager.h"

#include <filesystem>

#include "../PlatformUtils.h"
#include "../../Core/Logger.h"

namespace Simulacra
{
    struct FileManager
    {
        std::string WorkingDirectory;
    };

    static FileManager s_FileManager; 
    void CreateFilePlatformSubsystem()
    {
        // TODO(Edmund): To refactor to account user config path
        std::filesystem::current_path("../../..");
        s_FileManager.WorkingDirectory= std::filesystem::current_path().string();
        ConsoleLog("Current Working Directory: {}", s_FileManager.WorkingDirectory);
    }

    std::string FormatFilepath(const std::string& path)
    {
        std::filesystem::path fmtPath = std::filesystem::path(path).make_preferred();

        return s_FileManager.WorkingDirectory + std::filesystem::path("\\").make_preferred().string() + fmtPath.string() ;
    }
}
