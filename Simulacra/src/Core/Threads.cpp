#include "Threads.h"

namespace Simulacra
{
    std::vector<std::thread> e_WorkingThreads;

    void StartThreadsSubsystem()
    {
    }

    void ShutdownThreadsSubsystem()
    {
        WaitAllThreads();
    }

    void WaitAllThreads()
    {
        for (auto& t : e_WorkingThreads)
        {
            if (t.joinable())
                t.join();
        }
    }
}