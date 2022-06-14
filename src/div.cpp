#include "mv.h"

#if 1
MV operator/(MV a, MV b) {
#pragma gpc begin
    gaalop_div_a = mv_from_array(a);
    gaalop_div_b = mv_from_array(b);
#pragma clucalc begin
    ? gaalop_div_res = gaalop_div_a / gaalop_div_b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_div_res);
    return mv;
#pragma gpc end
}
#endif
