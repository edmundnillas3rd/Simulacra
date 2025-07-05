#include "FileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"

namespace Simulacra
{
    struct FileSystemProps
    {
        std::filesystem::path WorkingDirectory;
    };

    static FileSystemProps s_FileManager; 

    void StartFileSubsystem(const std::filesystem::path& path)
    {
        if (!path.empty())
            std::filesystem::current_path(path);

        s_FileManager.WorkingDirectory = std::filesystem::current_path();

        ConsoleLog("Current Working Directory: {}", s_FileManager.WorkingDirectory.string());
    }

    std::filesystem::path FormatFilepath(std::filesystem::path path)
    {
        return s_FileManager.WorkingDirectory /  path.make_preferred();
    }
}
