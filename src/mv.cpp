#include "mv.h"

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

coeff& MV::operator[](size_t blade) {
    return coeffs[blade];
}
