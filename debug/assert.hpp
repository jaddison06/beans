#pragma once

#include "Log.hpp"
#include "config.hpp"
#include <stdlib.h>

#define assertion_failed(cond) "Assertion failed: %s (%s, line %i)", #cond, __FILE__, __LINE__

#if BEANS_DBG_ASSERTS

#define ASSERT(cond) \
    if (!(cond)) { \
        Log::Error(assertion_failed(cond)); \
        exit(EXIT_FAILURE); \
    }

#else

#define ASSERT(cond) \
    if (!(cond)) { \
        Log::Warning(assertion_failed(cond)); \
    }

#endif