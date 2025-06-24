#include "FileManager.h"

#include "../Platform/PlatformUtils.h"
#include "Logger.h"

namespace Simulacra
{
    struct FileManagerProps
    {
        std::filesystem::path WorkingDirectory;
    };

    static FileManagerProps s_FileManager; 

    void StartFileSubsystem(std::filesystem::path path)
    {
        // TODO(Edmund): To refactor to account user config path
        std::filesystem::current_path("../../..");

        s_FileManager.WorkingDirectory = std::filesystem::current_path();

        ConsoleLog("Current Working Directory: {}", s_FileManager.WorkingDirectory.string());
    }

    std::filesystem::path FormatFilepath(std::filesystem::path path)
    {
        return s_FileManager.WorkingDirectory /  path.make_preferred();
    }
}
