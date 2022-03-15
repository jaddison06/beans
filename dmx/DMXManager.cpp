#include "DMXManager.hpp"
#include "ComboInterface.hpp"

#include <string.h>

using namespace beans;

DMXManager::DMXManager() {
    memset(interfaces, 0, BEANS_MAX_UNIS);
    interfaces[0] = new 
}

DMXManager::~DMXManager() {
    for (int i = 0; i < BEANS_MAX_UNIS; i++) {
        if (interfaces[i] != 0) {
            delete interfaces[i];
        }
    }
}

DMXInterface* DMXManager::GetInterface(uint16_t universe) {
    universe--;
    if (interfaces[universe] == 0) {
        interfaces[universe] = new ComboInterface;
    }
    return interfaces[universe];
}