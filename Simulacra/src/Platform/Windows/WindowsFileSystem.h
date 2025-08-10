#pragma once
#include "spch.h"

namespace Simulacra
{
    struct PlatformFileHandle
    {
        HANDLE Handle;
        HANDLE Event;
    };

    struct ProtectedWatchResource
    {
        explicit ProtectedWatchResource(PlatformFileHandle platformFileHandle)
            : Handle(platformFileHandle) 
        {
            Mutex = std::make_unique<std::mutex>();
        }
        
        PlatformFileHandle Handle;
        std::unique_ptr<std::mutex> Mutex;
    };

    PlatformFileHandle CreateWindowsFileHandle(const std::filesystem::path& path);

    void WatchWindowsDirectory(ProtectedWatchResource& resource, const std::function<void(void)>& callback);

    void CloseWatchWindowsDirectory(const PlatformFileHandle& data);
}