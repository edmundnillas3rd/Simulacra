#pragma once

#ifdef _WIN32

#ifdef _DEBUG
#define AddBreakpoint() DebugBreak()
#elif
#define AddBreakpoint()
#endif

#endif