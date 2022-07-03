#include "render.h"
#include "mv.h"

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

// function dState([M,B]) {
//   return  [
//     -0.5 * M * B,
//     -0.5 * (B.Dual*B - B*B.Dual).UnDual
//   ]
// }


struct Particle {
    MV motor = create_translator(
        create_vector(WIDTH/2.0, HEIGHT/2.0));
    MV vel;

    MV position() {
        return create_point() << motor;
    }
};

Particle particle;

void update(double dt) {
}

void draw() {
    MV pos = particle.position();
    draw_point(pos.x(), pos.y(), BLUE);
}
