#pragma once

#include <Simulacra.h>

#define Severe(...) SIM_LOG_ERROR(__VA_ARGS__)

#ifdef NDEBUG
#define Assert (expr) ((void)0)
#else
#define Assert(expr) \
    ((expr) ? (void)0 : \
        Severe("Assertion \"{}\" failed in {}, line {} ", \
                #expr, __FILE__, __LINE__))
#endif