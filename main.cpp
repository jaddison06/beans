#include "wm/Window.hpp"
#include "dmx/SACN.hpp"

#include <windows.h>

#include <stdio.h>
#include <thread>
#include <vector>

using namespace beans;

static bool quit = false;

void StartSacn() {
    auto sacn = new SACNInterface("beans", "127.0.0.1", 1);

    UniverseData data;
    memset(data, 0, 512);

    while (!quit) {
        sacn->Send(data);
        memset(data, data[0] + 1, 5);
        Sleep(800);
    }

    delete sacn;
}

int main(int argc, char** argv) {
    auto win = new Window();

    std::vector<std::thread*> threads = {
        new std::thread(StartSacn)
    };
    
    win->Start();

    quit = true;

    for (auto thread : threads) {
        thread->join();
        delete thread;
    }

    delete win;
    

    return 0;
}