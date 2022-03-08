#include "Window.hpp"

#include "SDLDisplay.hpp"
#include "SDLEvent.hpp"

#include <chrono>
#include <stdio.h>

using namespace beans;

Window::Window() {
    display = new SDLDisplay("beans");
    platformEvent = new SDLEvent();

    ui = new UI();
}

Window::~Window() {
    delete platformEvent;
    delete display;

    delete ui;
}

void Window::Start() {
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
    printf("%i frames in %f seconds = %f fps\n", frameCount, elapsed, frameCount / elapsed);

    delete event;
}