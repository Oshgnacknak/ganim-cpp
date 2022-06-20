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

MV operator^(MV a, MV b) {
#pragma gpc begin
    gaalop_outer_prod_a = mv_from_array(a);
    gaalop_outer_prod_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_outer_prod_res = gaalop_outer_prod_a ^ gaalop_outer_prod_b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_outer_prod_res);
    return mv;
#pragma gpc end
}

int main() {
    MV a = create_point(0, 0, +1);
    MV b = create_point(0, 0, -1);

    MV l = a ^ b;
    MV r = create_rotor(3.1415, l);

    MV x = create_point(1, 0, 0);
    println("Before: ", x);
    x = x << r;
    println("After: ", x);
}

int main2() {
    // open_window();
    // Defer close_the_window([&] {
    //     close_window();
    // });

    double last = current_time();

    MV center = create_point(WIDTH/2, HEIGHT/2);

    MV point = create_vector(WIDTH/2 + 20.0, HEIGHT/2 - 50.0);

    while (running) {
        double now = current_time();
        double dt = now - last;

        if (should_close_window()) {
            running = false;
        }

        MV trans = create_translator(create_vector(500, 300) * dt);

        point <<= trans;

        // begin_render();
        println(point);
        // end_render();

        double last = now;
    }

    return 0; 
}

#define OSH_H_IMPLEMENTATION
#include "osh.h"
