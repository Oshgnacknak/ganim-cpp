#include "mv.h"

MV& operator<<=(MV& a, MV b) {
#pragma gpc begin
    gaalop_sandwich_eq_a = mv_from_array(a);
    gaalop_sandwich_eq_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_sandwich_eq_res = gaalop_sandwich_eq_b * gaalop_sandwich_eq_a * ~gaalop_sandwich_eq_b;
#pragma clucalc end
    a = mv_to_array(gaalop_sandwich_eq_res);
    return a;
#pragma gpc end
}

MV operator<<(MV a, MV b) {
#pragma gpc begin
    gaalop_sandwich_a = mv_from_array(a);
    gaalop_sandwich_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_sandwich_res = gaalop_sandwich_b * gaalop_sandwich_a * ~gaalop_sandwich_b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_sandwich_res);
    return mv;
#pragma gpc end
}
