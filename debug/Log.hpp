#pragma once

#include <stdio.h>
#include <stdarg.h>

namespace beans::Log {
    void Info(const char* message, ...);
    void Warning(const char* message, ...);
    void Error(const char* message, ...);
}