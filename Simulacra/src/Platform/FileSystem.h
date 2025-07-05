#pragma once

#include <filesystem>

namespace Simulacra
{
    void StartFileSubsystem(const std::filesystem::path& path = "");

    std::filesystem::path FormatFilepath(std::filesystem::path path);
}