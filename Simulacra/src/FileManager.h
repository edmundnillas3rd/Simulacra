#pragma once

#include <string>

namespace Simulacra
{
    void StartFileSubsystem();

    void CreateFilePlatformSubsystem();
    std::string FormatFilepath(const std::string& path);
}