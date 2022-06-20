#include "mv.h"

#include <cmath>

coeff MV::s() {
#pragma gpc begin
    mv_s = mv_from_array(coeffs);
#pragma clucalc begin
    ? mv_ss = mv_s;
#pragma clucalc end
    return mv_get_bladecoeff(mv_ss, 1);
#pragma gpc end
}

coeff MV::x() {
#pragma gpc begin
    mv_x = mv_from_array(coeffs);
#pragma clucalc begin
    ? mv_xx = mv_x;
#pragma clucalc end
    return mv_get_bladecoeff(mv_xx, e1);
#pragma gpc end
}

coeff MV::y() {
#pragma gpc begin
    mv_y = mv_from_array(coeffs);
#pragma clucalc begin
    ? mv_yy = mv_y;
#pragma clucalc end
    return mv_get_bladecoeff(mv_yy, e1);
#pragma gpc end
}

MV operator+(MV a, MV b) {
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

MV operator-(MV a, MV b) {
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

MV operator*(MV a, MV b) {
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

MV operator*(MV a, coeff b) {
#pragma gpc begin
    gaalop_times_scalar_a = mv_from_array(a);
#pragma clucalc begin
    ? gaalop_times_scalar_res = gaalop_times_scalar_a * b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_times_scalar_res);
    return mv;
#pragma gpc end
}

MV& operator*=(MV& a, coeff b) {
#pragma gpc begin
    gaalop_times_scalar_eq_a = mv_from_array(a);
#pragma clucalc begin
    ? gaalop_times_scalar_eq_res = gaalop_times_scalar_eq_a * b;
#pragma clucalc end
    a = mv_to_array(gaalop_times_scalar_eq_res);
    return a;
#pragma gpc end
}

MV operator/(MV a, coeff b) {
#pragma gpc begin
    gaalop_div_scalar_a = mv_from_array(a);
#pragma clucalc begin
    ? gaalop_div_scalar_res = gaalop_div_scalar_a / b;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(gaalop_div_scalar_res);
    return mv;
#pragma gpc end
}

MV& operator/=(MV& a, coeff b) {
#pragma gpc begin
    gaalop_div_scalar_eq_a = mv_from_array(a);
#pragma clucalc begin
    ? gaalop_div_scalar_eq_res = gaalop_div_scalar_eq_a / b;
#pragma clucalc end
    a = mv_to_array(gaalop_div_scalar_eq_res);
    return a;
#pragma gpc end
}

coeff length(MV mv) {
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

MV create_point(coeff x, coeff y) {
#pragma gpc begin
#pragma clucalc begin
    ? create_point_res = createPoint(x, y, 0);
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_point_res);
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

MV create_vector(coeff x, coeff y) {
#pragma gpc begin
#pragma clucalc begin
    ? vector_res = x*e1 + y*e2;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(vector_res);
    return mv;
#pragma gpc end
}

coeff& MV::operator[](size_t blade) {
    return coeffs[blade];
}

MV create_rotor(coeff angle, MV axis) {
    coeff x = cos(angle/2);
    coeff y = sin(angle/2);
#pragma gpc begin
    create_rotor_axis = mv_from_array(axis);
#pragma clucalc begin
    ? create_rotor_res = x - e1*e2*y;
#pragma clucalc end
    MV mv;
    mv = mv_to_array(create_rotor_res);
    return mv;
#pragma gpc end
}

void print1(osh::Formatter auto& fmt, MV& mv) {
#pragma gpc begin
    mv_print1_mv = mv_from_array(mv);
#pragma clucalc begin
    ? mv_print1_res = mv_print1_mv;
#pragma clucalc end
    printp(fmt, mv_get_bladecoeff(mv_print1_res, 1.0));

    if (mv_get_bladecoeff(mv_print1_res, e1) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1), "e1");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2), "e2");
    }
    if (mv_get_bladecoeff(mv_print1_res, e3) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e3), "e3");
    }
    if (mv_get_bladecoeff(mv_print1_res, einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, einf), "einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e0), "e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2), "e1^e2");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e3) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e3), "e1^e3");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^einf), "e1^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e0), "e1^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^e3) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^e3), "e2^e3");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^einf), "e2^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^e0), "e2^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e3^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e3^einf), "e3^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e3^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e3^e0), "e3^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, einf^e0), "einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^e3) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^e3), "e1^e2^e3");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^einf), "e1^e2^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^e0), "e1^e2^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e3^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e3^einf), "e1^e3^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e3^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e3^e0), "e1^e3^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^einf^e0), "e1^einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^e3^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^e3^einf), "e2^e3^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^e3^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^e3^e0), "e2^e3^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^einf^e0), "e2^einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e3^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e3^einf^e0), "e3^einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^e3^einf) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^e3^einf), "e1^e2^e3^einf");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^e3^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^e3^e0), "e1^e2^e3^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^einf^e0), "e1^e2^einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e3^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e3^einf^e0), "e1^e3^einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e2^e3^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e2^e3^einf^e0), "e2^e3^einf^e0");
    }
    if (mv_get_bladecoeff(mv_print1_res, e1^e2^e3^einf^e0) != 0) {
        printp(fmt, " + ", mv_get_bladecoeff(mv_print1_res, e1^e2^e3^einf^e0), "e1^e2^e3^einf^e0");
    }
#pragma gpc end
}
