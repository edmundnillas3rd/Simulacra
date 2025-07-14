#include "FileSystem.h"

#include "Windows/WindowsFileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"
#include "../Core/Threads.h"

namespace Simulacra
{
    struct FileSystemAttr
    {
        ObserveData WatchData;
    };

    static FileSystemAttr s_FileSystemHandler; 

    void StartFileSubsystem(const std::filesystem::path& path)
    {
        if (!path.empty())
            std::filesystem::current_path(path);

        ConsoleLog("Current Working Directory: {}", std::filesystem::current_path().make_preferred().string());
    }

    void ShutdownFileSubsystem()
    {
        CloseWatchWindowsDirectory(s_FileSystemHandler.WatchData);
    }

    void WatchDirectory(std::filesystem::path path, const std::function<void(void)>& callback)
    {
        ObserveData data = CreateWindowsFileHandle(path);

        SubmitThread(std::thread(WatchWindowsDirectory, data, callback));

        s_FileSystemHandler.WatchData = data;
    }

    std::filesystem::path FormatFilepath(std::filesystem::path path)
    {
        return (std::filesystem::current_path() /  path).make_preferred();
    }
}
