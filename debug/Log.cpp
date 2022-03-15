#include "Log.hpp"
#include "config.hpp"

namespace beans::Log {
#if BEANS_DBG_LOGGING

#define LogLevel(name, startCode) \
    void name(const char* message, ...) { \
        va_list args; \
        va_start(args, message); \
        Log(startCode, #name, message, args); \
        va_end(args); \
    }

#else

#define LogLevel(name, startCode) void name(const char* message, ...) {}

#endif

    static void Log(const char* start, const char* level, const char* message, va_list args) {
        fprintf(stderr, "%s[%s] ", start, level);
        vfprintf(stderr, message, args);
        fprintf(stderr, "\u001b[0m\n");
    }

    LogLevel(Info, "\u001b[32m")
    LogLevel(Warning, "\u001b[31;1m")
    LogLevel(Error, "\u001b[31m")
}