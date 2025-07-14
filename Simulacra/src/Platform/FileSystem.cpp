#include "FileSystem.h"

#include "Windows/WindowsFileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"

namespace Simulacra
{
    struct FileSystemProps
    {
        std::vector<std::thread> WorkingThreads;
    };

    static FileSystemProps s_FileManager; 

    void StartFileSubsystem(const std::filesystem::path& path)
    {
        if (!path.empty())
            std::filesystem::current_path(path);

        ConsoleLog("Current Working Directory: {}", std::filesystem::current_path().make_preferred().string());
    }

    void WatchDirectory(const std::filesystem::path& path, const std::function<void(void)>& callback)
    {
        ObserveData data = CreateWindowsFileHandle(path);
        s_FileManager.WorkingThreads.emplace_back(std::thread([data, callback]() { 
            WatchWindowsDirectory(data, callback);
        }));
        s_FileManager.WorkingThreads.back().detach();
    }

    std::filesystem::path FormatFilepath(std::filesystem::path path)
    {
        return std::filesystem::current_path() /  path.make_preferred();
    }
}
