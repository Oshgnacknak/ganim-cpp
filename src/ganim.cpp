#include <iostream>
#include <cmath>

#include "clock.h"
#include "mv.h"
#include "render.h"

using namespace std;

bool running = true;

MV create_point(coeff x=0, coeff y=0, coeff z=0) {
#pragma gpc begin
#pragma clucalc begin
    ? create_point_res = createPoint(x, y, z);
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_point_res);
    return mv;
#pragma gpc end
}

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

MV create_rotor(coeff angle, MV axis) {
    coeff x = cos(angle/2);
    coeff y = sin(angle/2);
#pragma gpc begin
    create_rotor_axis = mv_from_array(axis);
#pragma clucalc begin
    ? create_rotor_res = x - e1^e2^e3 * y;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_rotor_res);
    return mv;
#pragma gpc end
}

int main() {
    open_window();
    double last = current_time();

    MV center = create_point(WIDTH/2, HEIGHT/2);

    MV point = vector(WIDTH/2 + 20.0, HEIGHT/2 - 50.0);

    while (running) {
        double now = current_time();
        double dt = now - last;

        if (should_close_window()) {
            running = false;
        }

        MV trans = create_translator(vector(500, 300) * dt);

        point <<= trans;

        begin_render();
        cout << "x: " << point.x() << " y: " << point.y() << endl;
        draw_point(point.x(), point.y(), RED);
        end_render();

        double last = now;
    }

    close_window();
    return 0; 
}
