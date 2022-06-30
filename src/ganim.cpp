#include <cmath>

#include "clock.h"
#include "mv.h"
#include "render.h"

const int FPS = 60;
const double UPDATE_DELAY = 1.0 / FPS;

using namespace osh;

bool running = true;

MV create_translator(MV t) {
#pragma gpc begin
    create_translator_t = mv_from_array(t);
#pragma clucalc begin
    ? create_translator_res = 1 - 0.5 * create_translator_t * einf;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_translator_res);
    return mv;
#pragma gpc end
}

struct Particle {
    MV motor = create_translator(
        create_vector(WIDTH/2.0, HEIGHT/2.0));
    MV vel;

    MV position() {
        return create_point() << motor;
    }
};

// function dState([M,B]) {
//   return  [
//     -0.5 * M * B,
//     -0.5 * (B.Dual*B - B*B.Dual).UnDual
//   ]
// }

int main() {
    open_window();
    Defer close_the_window([&] {
        close_window();
    });

    double last = current_time();

    Particle particle;

    MV point = create_point(WIDTH/2 - 60, HEIGHT/2);

    MV rotated = point;

    double acc = 0;
    while (running) {
        double now = current_time();
        double dt = now - last;

        if (should_close_window()) {
            running = false;
        }

        acc += dt;
        while (acc > UPDATE_DELAY) {
            MV rotor = create_rotor(0.12, create_point(WIDTH/2, HEIGHT/2));
            rotated <<= rotor;

            acc -= UPDATE_DELAY;
        }

        begin_render();
        draw_point(point.x(), point.y(), RED);
        draw_point(rotated.x(), rotated.y(), GREEN);

        MV pos = particle.position();
        draw_point(pos.x(), pos.y(), BLUE);
        end_render();

        last = now;
    }

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
