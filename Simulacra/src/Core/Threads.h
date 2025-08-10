#pragma once

#include "spch.h"

namespace Simulacra
{
    void StartThreadsSubsystem();
    void ShutdownThreadsSubsystem();

    std::vector<std::thread>& GetWorkingThreads();

    template<typename F, typename... Args>
    void SubmitThread(const F& threadFunction, Args&&... args)
    {
        GetWorkingThreads().emplace_back(threadFunction, std::forward<Args>(args)...);
    }

    void WaitAllThreads();
}