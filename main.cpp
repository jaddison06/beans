#include "dmx/SACN.hpp"

#include "core/FixtureData.hpp"
#include "core/Channel.hpp"
#include "core/Engine.hpp"
#include "core/DataSource.hpp"
#include "dmx/DMXManager.hpp"

#include "debug/Log.hpp"
#include "debug/assert.hpp"
#include "debug/perfcount.hpp"

#include <windows.h>

#include <stdio.h>
#include <thread>
#include <vector>

using namespace beans;

static bool quit = false;

int main(int argc, char** argv) {
    
    std::vector<std::thread*> threads = {

    };

    

    quit = true;

    for (auto thread : threads) {
        thread->join();
        delete thread;
    }

    
    return 0;
}