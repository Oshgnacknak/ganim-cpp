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

    Color color;

    MV vel;

    MV forques = { 0 };

    Particle() {
        color = {
            random<uint8_t>(120, 255),
            random<uint8_t>(120, 255),
            random<uint8_t>(120, 255)
        };

        vel = create_velocity(
            random(-300, 300), 
            random(-300, 300));
    }

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

    void draw() {
        MV pos = position();
        draw_point(pos.x(), pos.y(), color);
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

DArray<Particle> particles;

void init() {
    for (int i = 0; i < 20; i++) {
        particles.push(Particle());
    }
}

void update(double dt) {
    for (int i = 0; i < particles.size(); i++) {
        auto& particle = particles[i];

        particle.damping();
        particle.gravity();

        particle.update(dt);
    }
}

void draw() {
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
}
