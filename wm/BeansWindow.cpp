#include "BeansWindow.hpp"

#include "SDLDisplay.hpp"
#include "SDLEvent.hpp"

#include <chrono>
#include <stdio.h>

using namespace beans;

BeansWindow::BeansWindow() {
    display = new SDLDisplay("beans");
    platformEvent = new SDLEvent();

    ui = new BeansUI();
}

BeansWindow::~BeansWindow() {
    delete platformEvent;
    delete display;

    delete ui;
}

void BeansWindow::Start() {
    auto event = new Event;

    auto start = std::chrono::high_resolution_clock::now();

    while (!quit) {
        while (platformEvent->Poll(event) > 0) {
            if (event->type == EventType::Quit) {
                quit = true;
            }
            if (!ui->OnEvent(event)) {
                quit = true;
            }
        }
        ui->Draw(display);
        display->Flush();

        frameCount++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = ((double)((end - start).count())) / 1000000000;
    printf("%i frames in %f seconds = %f fps", frameCount, elapsed, frameCount / elapsed);

    delete event;
}