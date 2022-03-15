#include "dmx/SACN.hpp"

#include "core/FixtureData.hpp"
#include "core/Channel.hpp"
#include "core/Engine.hpp"
#include "core/DataSource.hpp"

#include <windows.h>

#include <stdio.h>
#include <thread>
#include <vector>

using namespace beans;

static bool quit = false;

int main(int argc, char** argv) {
    auto sacn = new SACNInterface("beans", "127.0.0.1", 1);

    auto engine = new Engine();
    auto chan = new Channel(FixtureData("fixtures/test.bfix", "4ch"));
    auto ds = new DataSource();

    engine->universes.push_back({
        1,
        {
            EngineChannel {
                1,
                chan,
                ds,
                {}
            }
        },
        sacn
    });
    
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