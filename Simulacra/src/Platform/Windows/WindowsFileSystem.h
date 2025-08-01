#pragma once
#include "spch.h"

namespace Simulacra
{
    struct PlatformFileHandle
    {
        HANDLE Handle;
        HANDLE Event;
    };

    PlatformFileHandle CreateWindowsFileHandle(const std::filesystem::path& path);

    void WatchWindowsDirectory(const PlatformFileHandle& data, const std::function<void(void)>& callback);

    void CloseWatchWindowsDirectory(const PlatformFileHandle& data);

    std::vector<std::string> GetListFilesInDirectory(const std::filesystem::path& path);
}