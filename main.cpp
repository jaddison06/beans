#include "dmx/SACN.hpp"

#include "core/FixtureData.hpp"
#include "core/Channel.hpp"
#include "core/Engine.hpp"
#include "core/DataSource.hpp"
#include "dmx/DMXManager.hpp"

#include "debug/Log.hpp"
#include "debug/assert.hpp"

#include <windows.h>

#include <stdio.h>
#include <thread>
#include <vector>

using namespace beans;

static bool quit = false;

int main(int argc, char** argv) {
    auto mgr = new DMXManager();
    auto engine = new Engine();

    Log::Info("Loading patch");

    engine->LoadPatch("test_data/patch.bpat", mgr);

    Log::Info("Starting main loop");

    while (true) {
        //Log::Info("Ticking");
        //engine->Tick();
        Sleep(600);
    }

    std::vector<std::thread*> threads = {

    };

    quit = true;

    for (auto thread : threads) {
        thread->join();
        delete thread;
    }
    
    return 0;
}