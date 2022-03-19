#pragma once

#include "config.hpp"
#include <string>

namespace beans {
    void perfcountStart();
    void perfcountEnd(std::string funcName);
}

#if BEANS_DBG_PERFCOUNT

#define PERFCOUNT_START() perfcountStart()
#define PERFCOUNT_END() perfcountEnd(__func__)

#else

#define PERFCOUNT_START()
#define PERFCOUNT_END()

#endif