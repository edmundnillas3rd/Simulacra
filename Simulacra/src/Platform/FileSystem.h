#pragma once

#include <filesystem>
#include "Windows/WindowsFileSystem.h"

namespace Simulacra
{
    void StartFileSubsystem(const std::filesystem::path& path = "");
    void ShutdownFileSubsystem();

    void WatchDirectory(std::filesystem::path path, const std::function<void(void)>& callback);
}