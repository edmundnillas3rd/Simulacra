#pragma once

#ifdef SIMULACRA_WINDOWS

#ifdef _DEBUG
#define AddBreakpoint() DebugBreak()
#elif
#define AddBreakpoint()
#endif

#define SIMULACRA_ASSERT(exp, msg) assert((void(msg), exp))

#endif