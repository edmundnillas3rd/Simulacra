#pragma once
#include "spch.h"

namespace Simulacra
{
    void WatchWindowsDirectory(const std::filesystem::path& path, const std::function<void(void)>& callback);
}