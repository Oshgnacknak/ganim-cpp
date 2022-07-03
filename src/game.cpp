#include "render.h"
#include "mv.h"

MV create_motor(MV from, MV to) {
#pragma gpc begin
    create_motor_from = mv_from_array(from);
    create_motor_to = mv_from_array(to);
#pragma clucalc begin
    ? create_motor_res = 1 + create_motor_from/create_motor_to;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_motor_res);
    return mv;
#pragma gpc end
}

struct Particle {
    MV motor = create_motor(
        create_point(0, 0),
        create_point(WIDTH/2.0, HEIGHT/2.0));
    MV vel = !create_vector(150, -100);

    MV position() {
        MV pos = !(create_point() << motor);
        pos /= -pos[E0];
        return pos;
    }

    void update(double dt) {
        MV dm = -0.5 * motor * vel;
        MV dv = !(- 0.5 * (!vel * vel - vel * !vel));
        motor += dt * dm;
        vel += dt * dv;
    }
};

Particle particle;

void update(double dt) {
    particle.update(dt);
}

void draw() {
    MV pos = particle.position();
    draw_point(pos.x(), pos.y(), BLUE);
}
