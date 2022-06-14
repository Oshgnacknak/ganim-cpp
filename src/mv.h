#ifndef MV_H
#define MV_H 

#include <cstddef>

#define __BLADES 1, \
                 e1, e2, e3, einf, e0, \
                 e1^e2, e1^e3, e1^einf, e1^e0, e2^e3, e2^einf, e2^e0, e3^einf, e3^e0, einf^e0, \
                 e1^e2^e3, e1^e2^einf, e1^e2^e0, e1^e3^einf, e1^e3^e0, e1^einf^e0, e2^e3^einf, e2^e3^e0, e2^einf^e0, e3^einf^e0, \
                 e1^e2^e3^einf, e1^e2^e3^e0, e1^e2^einf^e0, e1^e3^einf^e0, e2^e3^einf^e0, \
                 e1^e2^e3^einf^e0

#define mv_to_array(mv) mv_to_array(mv, __BLADES)

#define mv_from_array(array) mv_from_array(array, __BLADES)

using coeff = double;

struct MV {
    coeff coeffs[32] = { 0 };

    coeff& operator[](size_t);

    coeff s();
    coeff x();
    coeff y();
};

MV& operator+=(MV, MV);

MV& operator-=(MV, MV);

MV& operator*=(MV, MV);

MV& operator/=(MV, MV);

MV operator+(MV, MV);

MV operator-(MV, MV);

MV operator*(MV, MV);

MV operator/(MV, MV);

MV operator*(MV, coeff);
MV operator*(coeff, MV);

MV& operator*=(MV, coeff);

coeff length(MV mv);

MV vector(coeff x = 0, coeff y = 0, coeff z = 0);

#endif /* MV_H */
