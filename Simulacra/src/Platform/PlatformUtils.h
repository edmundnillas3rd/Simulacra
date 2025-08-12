#pragma once

#ifdef SIMULACRA_WINDOWS

#ifdef _DEBUG
#define AddBreakpoint() DebugBreak()
#else
#define AddBreakpoint()
#endif

#define SIMULACRA_ASSERT(exp, msg) assert((void(msg), exp))

#endif