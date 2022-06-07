#include "mv.h"

#include <cmath>

MV operator+(MV& a, MV& b) {
#pragma gpc begin
    gaalop_add_a = mv_from_array(a);
    gaalop_add_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_add_res = gaalop_add_a + gaalop_add_b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_add_res);
    return mv;
#pragma gpc end
}

MV operator-(MV& a, MV& b) {
#pragma gpc begin
    gaalop_sub_a = mv_from_array(a);
    gaalop_sub_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_sub_res = gaalop_sub_a - gaalop_sub_b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_sub_res);
    return mv;
#pragma gpc end
}

MV operator*(MV& a, MV& b) {
#pragma gpc begin
    gaalop_times_a = mv_from_array(a);
    gaalop_times_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_times_res = gaalop_times_a * gaalop_times_b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_times_res);
    return mv;
#pragma gpc end
}

MV& operator*=(MV& a, coeff b) {
#pragma gpc begin
    gaalop_times_scalar_a = mv_from_array(a);
#pragma clucalc begin
    ? gaalop_times_scalar_res = gaalop_times_scalar_a * b;
#pragma clucalc end
    a = mv_to_array(gaalop_times_scalar_res);
    return a;
#pragma gpc end
}

coeff length(MV& mv) {
#pragma gpc begin
    length_mv = mv_from_array(mv);
#pragma clucalc begin
    ? length_sq = length_mv . length_mv;
#pragma clucalc end
    coeff sq;
    sq = mv_get_bladecoeff(length_sq, 1.0);
    return sqrt(sq);
#pragma gpc end
}

MV vector(coeff x, coeff y, coeff z) {
#pragma gpc begin
#pragma clucalc begin
    ? vector_res = x*e1 + y*e2 + z*e3;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(vector_res);
    return mv;
#pragma gpc end
}

coeff& MV::operator[](size_t blade) {
    return coeffs[blade];
}
