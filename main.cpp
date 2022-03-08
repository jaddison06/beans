#include "wm/Window.hpp"
#include "dmx/SACN.hpp"

#include <windows.h>

#include <stdio.h>
#include <thread>

using namespace beans;

static bool quit = false;

void StartSacn(SACNInterface* sacn) {
    printf("StartSacn\n");

    UniverseData data;
    memset(data, 0, 512);

    while (!quit) {
        sacn->Send(data);
        memset(data, data[0] + 1, 5);
        Sleep(800);
    }
}

void StartUI(Window* window) {
    printf("StartUI\n");
    window->Start();
    printf("eeeee\n");
}

int main(int argc, char** argv) {
    auto sacn = new SACNInterface("beans", "127.0.0.1", 1);
    auto window = new Window();

    std::thread sacnThread(StartSacn, sacn);
    
    StartUI(window);

    quit = true;

    sacnThread.join();

    delete window;
    delete sacn;
    

    return 0;
}