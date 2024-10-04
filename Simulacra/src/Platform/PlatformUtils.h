#pragma once

#ifdef _WIN32 && DEBUG 
    #define WIN32_LEAN_AND_MEAN   
    #define NOCOMM
    #include <windows.h>

    #define SetBreakpoint() DebugBreak()
#endif