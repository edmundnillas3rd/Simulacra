#include "FileSystem.h"
#include "src/Core/Log.h"

namespace Simulacra
{
    FileSystem filesystem;

    void SetCWDPath(const std::string& path)
    {
        std::filesystem::current_path(path);
        std::string currentPath = std::filesystem::current_path().string().append("\\");
        filesystem.cwd.append(currentPath);
        SIM_LOG_INFO("Current Simulacra Working Directory: {}", filesystem.cwd);
    }
}
