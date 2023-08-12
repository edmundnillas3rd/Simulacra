#pragma once

namespace Simulacra
{
    struct FileSystem
    {
        std::string cwd;
    };

    extern FileSystem filesystem;

    void SetCWDPath(const std::string& path);
}