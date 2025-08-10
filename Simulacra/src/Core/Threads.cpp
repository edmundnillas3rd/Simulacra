#include "Threads.h"

namespace Simulacra
{
    static std::vector<std::thread> s_WorkingThreads;

    void StartThreadsSubsystem()
    {
    }

    void ShutdownThreadsSubsystem()
    {
        WaitAllThreads();
    }

    std::vector<std::thread>& GetWorkingThreads()
    {
        return s_WorkingThreads;
    }

    void WaitAllThreads()
    {
        for (auto& thread : s_WorkingThreads)
        {
            if (thread.joinable())
                thread.join();
        }

        s_WorkingThreads.clear();
    }
}