#pragma once
#include "spch.h"

namespace Simulacra
{
    class FileWatch
    {
    public:
        explicit FileWatch(const std::filesystem::path& path, const std::function<void()>& func);
        ~FileWatch();
    private:
        void WatchWindowsDirectory();

        HANDLE m_File;
        HANDLE m_Event;
        std::mutex m_Mutex;

        std::function<void()> m_Callback;
    };

}