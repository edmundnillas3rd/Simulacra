#pragma once

#include <filesystem>

namespace Simulacra
{
    void StartFileSubsystem(const std::filesystem::path& path = "");
    void ShutdownFileSubsystem();

    void WatchDirectory(std::filesystem::path path, const std::function<void(void)>& callback);
    std::filesystem::path FormatFilepath(std::filesystem::path path);
}