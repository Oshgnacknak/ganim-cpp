#include <cmath>

#include "clock.h"
#include "mv.h"
#include "game.h"
#include "render.h"

const int FPS = 60;
const double UPDATE_DELAY = 1.0 / FPS;

using namespace osh;

bool running = true;

int main() {
    OSH_H_MAIN_INIT();

    open_window();
    Defer close_the_window([&] {
        close_window();
    });

    init();

    double last = current_time();

    double acc = 0;
    while (running) {
        double now = current_time();
        double dt = now - last;

        if (should_close_window()) {
            running = false;
        }

        acc += dt;
        while (acc > UPDATE_DELAY) {
            update(UPDATE_DELAY);
            acc -= UPDATE_DELAY;
        }

        begin_render();
        draw();
        end_render();

        last = now;
    }

    return 0; 
}
