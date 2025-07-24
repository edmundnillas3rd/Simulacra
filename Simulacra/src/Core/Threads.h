#pragma once

#include "spch.h"

namespace Simulacra
{
    void StartThreadsSubsystem();
    void ShutdownThreadsSubsystem();

    void SubmitThread(const std::function<void()>& threadFunction);
    void WaitAllThreads();
}