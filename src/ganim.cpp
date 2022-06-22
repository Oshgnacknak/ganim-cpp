#include <cmath>

#include "clock.h"
#include "mv.h"
#include "render.h"

using namespace osh;

bool running = true;

MV create_translator(MV delta) {
#pragma gpc begin
    create_translator_delta = mv_from_array(delta);
#pragma clucalc begin
    ? create_translator_res = 1 - 0.5*create_translator_delta*einf;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_translator_res);
    return mv;
#pragma gpc end
}

int main() {
    open_window();
    Defer close_the_window([&] {
        close_window();
    });

    double last = current_time();

    MV point = create_point(WIDTH-100, 120);

    while (running) {
        double now = current_time();
        double dt = now - last;

        if (should_close_window()) {
            running = false;
        }


        MV rotor = create_rotor(dt, {});
        MV rotated = point << rotor;

        begin_render();
        draw_point(point.x(), point.y(), RED);
        draw_point(rotated.x(), rotated.y(), GREEN);
        end_render();

        double last = now;
    }

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
