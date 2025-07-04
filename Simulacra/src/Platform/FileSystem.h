#pragma once

#include <filesystem>

#include "Windows/WinFileSystem.h"

namespace Simulacra
{
    void StartFileSubsystem(const std::filesystem::path& path = "");

    std::filesystem::path FormatFilepath(std::filesystem::path path);

    struct FileSystemAttr
    {
        FileHandle SystemFileHandle;
    };

    FileSystemAttr WatchDirectoryChanges(const std::filesystem::path& path);
    bool CheckDirectoryChanges(FileSystemAttr attr);
}