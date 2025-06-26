#pragma once

#ifdef _WIN32

#define WIN32_MEAN_AND_LEAN
#include <windows.h>

#ifdef _DEBUG
#define AddBreakpoint() DebugBreak()
#elif
#define AddBreakpoint()
#endif

#endif