#include "FileSystem.h"

#include "PlatformUtils.h"
#include "../Core/Logger.h"

namespace Simulacra
{
    struct FileManagerProps
    {
        std::filesystem::path WorkingDirectory;
    };

    static FileManagerProps s_FileManager; 

    void StartFileSubsystem(std::filesystem::path path)
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
