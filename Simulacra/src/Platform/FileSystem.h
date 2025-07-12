#pragma once

#include <filesystem>

namespace Simulacra
{
    void StartFileSubsystem(const std::filesystem::path& path = "");

    void WatchDirectory(const std::filesystem::path& path, const std::function<void(void)>& callback);
    std::filesystem::path FormatFilepath(std::filesystem::path path);
}