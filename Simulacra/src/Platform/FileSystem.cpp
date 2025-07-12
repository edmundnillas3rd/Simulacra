#include "FileSystem.h"

#include "Windows/WindowsFileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"

namespace Simulacra
{
    struct FileSystemProps
    {
        std::filesystem::path WorkingDirectory;

        std::vector<std::thread> WorkingThreads;
    };

    static FileSystemProps s_FileManager; 

    void StartFileSubsystem(const std::filesystem::path& path)
    {
        if (!path.empty())
            std::filesystem::current_path(path);

        s_FileManager.WorkingDirectory = std::filesystem::current_path();

        ConsoleLog("Current Working Directory: {}", s_FileManager.WorkingDirectory.string());
    }

    void WatchDirectory(const std::filesystem::path& path, const std::function<void(void)>& callback)
    {
        // s_FileManager.WorkingThreads.emplace_back(std::thread(WatchWindowsDirectory, std::cref(path), std::cref(callback)));
        s_FileManager.WorkingThreads.emplace_back(std::thread([path, callback]() { 
            WatchWindowsDirectory(path, callback);
        }));
        s_FileManager.WorkingThreads.back().detach();
    }

    std::filesystem::path FormatFilepath(std::filesystem::path path)
    {
        return s_FileManager.WorkingDirectory /  path.make_preferred();
    }
}
