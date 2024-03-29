#pragma once

#include <string>

namespace beans {
    struct Parameter {
        std::string name;
        int min, max, home;
        bool is16bit;
        int offset;
    };
}