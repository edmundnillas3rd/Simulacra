#include "FileSystem.h"
#include "src/Log.h"

namespace Simulacra
{
    FileSystem filesystem;

    void SetCWDPath(const std::string& path)
    {
        std::filesystem::current_path(path);
        filesystem.cwd = std::filesystem::current_path();
        filesystem.cwd = filesystem.cwd + "/";
        SIM_LOG_INFO("Current Simulacra Working Directory: {}", filesystem.cwd);
    }
}
