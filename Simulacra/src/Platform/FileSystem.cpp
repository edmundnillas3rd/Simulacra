#include "FileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"
#include "../Core/Threads.h"

namespace Simulacra
{
    struct FileSystemAttr
    {
        PlatformFileHandle WatchData;
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
        CloseWatchWindowsDirectory(s_FileSystemHandler.WatchData);
    }

    void WatchDirectory(std::filesystem::path path, const std::function<void(void)>& callback)
    {
        PlatformFileHandle data = CreateWindowsFileHandle(path);

        SubmitThread(std::bind(WatchWindowsDirectory, data, callback));

        s_FileSystemHandler.WatchData = data;
    }
}
