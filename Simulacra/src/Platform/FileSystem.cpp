#include "FileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"

#include "Windows/WindowsFileSystem.h"

namespace Simulacra
{
    struct FileSystemAttr
    {
        std::vector<std::unique_ptr<FileWatch>> FileWatchContainer;
    };

    static FileSystemAttr s_FileSystemHandler; 

    void StartFileSubsystem(const std::filesystem::path& path)
    {
        if (!path.empty())
            std::filesystem::current_path(path);

        SIMULACRA_LOG("Current Working Directory: {}", std::filesystem::current_path().make_preferred().string());
    }

    void ShutdownFileSubsystem()
    {
    }

    void WatchDirectory(std::filesystem::path path, const std::function<void(void)>& callback)
    {
        s_FileSystemHandler.FileWatchContainer.emplace_back(std::make_unique<FileWatch>(path, callback));
    }

    std::filesystem::directory_iterator ListFilesInDirectory(const std::filesystem::path& path)
    {
        return std::filesystem::directory_iterator(path);
    }
}
