#ifndef MV_H
#define MV_H 

#include "osh.h"

#include <cstddef>

#define __BLADES 1.0, \
                 e0, \
                 e1, \
                 e2, \
                 e0^e1, \
                 e0^e2, \
                 e1^e2, \
                 e0^e1^e2

const size_t ONE  = 0;
const size_t E0   = 1;
const size_t E1   = 2;
const size_t E2   = 3;
const size_t E01  = 4;
const size_t E02  = 5;
const size_t E12  = 6;
const size_t E012 = 7;

#define mv_to_array(mv) mv_to_array(mv, __BLADES)

#define mv_from_array(array) mv_from_array(array, __BLADES)

using coeff = double;

struct MV {
    coeff coeffs[8] = { 0 };

    coeff& operator[](size_t);

    coeff s();
    coeff x();
    coeff y();
};

MV& operator+=(MV&, MV);

MV& operator-=(MV&, MV);

MV& operator*=(MV&, MV);

MV& operator/=(MV&, MV);

MV& operator<<=(MV& a, MV b);

MV operator+(MV, MV);

MV operator-(MV, MV);

MV operator*(MV, MV);

MV operator/(MV, MV);

MV operator^(MV a, MV b);

MV operator<<(MV a, MV b);

MV operator!(MV);

MV operator*(MV, coeff);
MV operator*(coeff, MV);

MV operator/(MV, coeff);
MV operator/(coeff, MV);

MV& operator*=(MV&, coeff);
MV& operator/=(MV&, coeff);

coeff length(MV mv);

MV scalar(coeff s);

MV create_motor(MV from, MV to);

MV create_rotor(coeff angle, MV axis);

MV create_point(coeff x=0, coeff y=0);

MV create_vector(coeff x = 0, coeff y = 0);

void print1(osh::Formatter auto& fmt, MV& mv);

#endif /* MV_H */
