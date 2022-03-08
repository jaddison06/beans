#include "wm/BeansWindow.hpp"
#include "dmx/SACN.hpp"

#include <windows.h>

using namespace beans;

int main(int argc, char** argv) {
    /*
    auto win = new BeansWindow();

    win->Start();

    delete win;
    */
    auto sacn = new SACNInterface("beans", "127.0.0.1", 1);

    UniverseData data;
    memset(data, 0, 512);

    while (true) {
        sacn->Send(data);
        memset(data, data[0] + 1, 5);
        Sleep(800);
    }

    delete sacn;

    return 0;
}