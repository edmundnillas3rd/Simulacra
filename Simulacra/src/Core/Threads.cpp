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

    void SubmitThread(const std::function<void()>& threadFunction)
    {
        s_WorkingThreads.emplace_back(std::thread(threadFunction));
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