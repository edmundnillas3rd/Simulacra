#pragma once

#include "spch.h"

namespace Simulacra
{
    struct FileHandle
    {
        DWORD       WaitStatus;
        HANDLE      Handle;
    };

    FileHandle WatchWindowsDirectory(const std::filesystem::path& path);
    bool CheckWindowsDirectoryChanges(FileHandle handle);
}