#include "wm/BeansWindow.hpp"

using namespace beans;

int main(int argc, char** argv) {
    auto win = new BeansWindow();

    win->Start();

    delete win;

    return 0;
}