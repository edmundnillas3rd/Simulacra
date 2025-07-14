#pragma once

#include "spch.h"

namespace Simulacra
{
    extern std::vector<std::thread> e_WorkingThreads;

    void StartThreadsSubsystem();
    void ShutdownThreadsSubsystem();

    template<typename F>
    void SubmitThread(F threadFunction)
    {
        e_WorkingThreads.emplace_back(std::move(threadFunction));
    }
    void WaitAllThreads();
}