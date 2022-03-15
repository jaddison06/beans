#include "dmx/SACN.hpp"

#include "core/FixtureData.hpp"
#include "core/Channel.hpp"
#include "core/Engine.hpp"
#include "core/DataSource.hpp"
#include "dmx/DMXManager.hpp"

#include <windows.h>

#include <stdio.h>
#include <thread>
#include <vector>

using namespace beans;

static bool quit = false;

int main(int argc, char** argv) {
    auto sacn = new SACNInterface("beans", "127.0.0.1", 1);

    auto mgr = new DMXManager();
    auto engine = new Engine();

    engine->LoadPatch("test_data/patch.bpat", mgr);
    
    while (true) {
        engine->Tick();
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