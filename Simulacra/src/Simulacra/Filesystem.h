#pragma once

#include "Window.h"

namespace Simulacra
{
    struct FileSystem
    {
        std::string CurrenWorkingDirectory;
    };

    extern FileSystem FileManager;

    void InitializeFilesystem(Window window);
}