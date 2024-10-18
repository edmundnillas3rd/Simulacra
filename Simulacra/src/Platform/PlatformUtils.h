#pragma once

#ifdef _WIN32

    #include <windows.h>

    #define AddBreakpoint() DebugBreak()

#endif
