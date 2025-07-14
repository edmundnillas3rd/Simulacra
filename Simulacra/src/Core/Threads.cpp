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

    void SubmitThread(const std::function<void(void)> &threadFunction)
    {
        s_WorkingThreads.emplace_back(threadFunction);
    }

    void SubmitDetachThread(const std::function<void(void)> &detachThreadFunction)
    {
        s_WorkingThreads.emplace_back(detachThreadFunction);
        s_WorkingThreads.back().detach();
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