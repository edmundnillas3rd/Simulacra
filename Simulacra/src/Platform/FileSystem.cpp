#include "FileSystem.h"

#include "spch.h"

#include "../Core/Logger.h"
#include "../Core/Threads.h"

#include "Windows/WindowsFileSystem.h"

namespace Simulacra
{
    struct FileSystemAttr
    {
        std::vector<ProtectedWatchResource> WatchData;
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
        for (auto& fh : s_FileSystemHandler.WatchData)
            CloseWatchWindowsDirectory(fh.Handle);
    }

    void WatchDirectory(std::filesystem::path path, const std::function<void(void)>& callback)
    {
        s_FileSystemHandler.WatchData.emplace_back(ProtectedWatchResource(CreateWindowsFileHandle(path)));
        SubmitThread(WatchWindowsDirectory, std::ref(s_FileSystemHandler.WatchData.back()), callback);
    }

    std::filesystem::directory_iterator ListFilesInDirectory(const std::filesystem::path& path)
    {
        return std::filesystem::directory_iterator(path);
    }
}
