#pragma once

#include "spch.h"

namespace Simulacra
{
    void StartThreadsSubsystem();
    void ShutdownThreadsSubsystem();
    void SubmitThread(const std::function<void(void)>& threadFunction);
    void SubmitDetachThread(const std::function<void(void)>& detachThreadFunction);
    void WaitAllThreads();
}