#include "DMX.hpp"

#include <string.h>

using namespace beans;

DMXInterface::DMXInterface() {
    memset(data, 0, 512);
}