#pragma once

#ifdef _WIN32

    #define WIN32_MEAN_AND_LEAN
    #include <windows.h>

    #define AddBreakpoint() DebugBreak()

#endif
