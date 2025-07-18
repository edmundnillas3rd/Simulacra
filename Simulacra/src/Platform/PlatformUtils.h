#pragma once

#ifdef SIMULACRA_WINDOWS

#ifdef _DEBUG
#define AddBreakpoint() DebugBreak()
#elif
#define AddBreakpoint()
#endif

#endif