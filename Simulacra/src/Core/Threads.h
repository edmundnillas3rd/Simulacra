#pragma once

#include "spch.h"

namespace Simulacra
{
    void StartThreadsSubsystem();
    void ShutdownThreadsSubsystem();

    void SubmitThread(std::thread threadFunction);
    void WaitAllThreads();
}