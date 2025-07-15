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

    void SubmitThread(std::thread threadFunction)
    {
        s_WorkingThreads.emplace_back(std::move(threadFunction));
    }

    void WaitAllThreads()
    {
        for (auto& t : s_WorkingThreads)
        {
            if (t.joinable())
                t.join();
        }
    }
}