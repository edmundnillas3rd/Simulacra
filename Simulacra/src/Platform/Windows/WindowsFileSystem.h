#pragma once
#include "spch.h"

namespace Simulacra
{
    struct ObserveData
    {
        HANDLE Handle;
        HANDLE Event;
    };

    ObserveData CreateWindowsFileHandle(const std::filesystem::path& path);
    void WatchWindowsDirectory(const ObserveData& data, const std::function<void(void)>& callback);
    void CloseWatchWindowsDirectory(const ObserveData& data);
}