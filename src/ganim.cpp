#include <iostream>
#include <cmath>

#include "clock.h"
#include "mv.h"
#include "render.h"

using namespace std;

bool running = true;

int main() {
    open_window();
    double last = current_time();

    while (running) {
        double now = current_time();
        double dt = now - last;

        if (should_close_window()) {
            running = false;
        }

        MV center = vector(WIDTH/2, HEIGHT/2);

        MV point = center + vector(20.0, -50.0);

        begin_render();
        draw_point(point.x(), point.y(), RED);
        end_render();

        double last = now;
    }

    close_window();
    return 0; 
}
