#include "render.h"
#include "mv.h"

#define WORLD_GRAVITY 150

MV create_velocity(coeff x = 0, coeff y = 0) {
   return !create_vector(y, -x);
}

struct Particle {
    MV motor = create_motor(
        create_point(0, 0),
        create_point(WIDTH/2.0, HEIGHT/2.0));
    MV vel = create_velocity(300, -200);
    MV forques = { 0 };

    MV position() {
        MV pos = !(create_point() << motor);
        pos /= -pos[E0];
        return pos;
    }

    void update(double dt) {
        MV dm = -0.5 * motor * vel;
        MV dv = !(forques - 0.5 * (!vel * vel - vel * !vel));

        motor += dt * dm;
        vel += dt * dv;

        forques = { 0 };
    }

    void applyForque(MV forque) {
        forques += forque;
    }

    void damping() {
        MV damping = !(-0.15 * vel);
        applyForque(damping);
    }

    void gravity() {
#pragma gpc begin
        particle_gravity_motor = mv_from_array(motor);
#pragma clucalc begin
        ? particle_gravity_res = *(particle_gravity_motor * -WORLD_GRAVITY * e0^e2 * ~particle_gravity_motor);
#pragma clucalc end
        MV mv;
        mv = mv_to_array(particle_gravity_res);
        applyForque(mv);
#pragma gpc end
    }
};

Particle particle;

void update(double dt) {
    particle.damping();
    particle.gravity();

    particle.update(dt);
}

void draw() {
    MV pos = particle.position();
    draw_point(pos.x(), pos.y(), BLUE);
}
