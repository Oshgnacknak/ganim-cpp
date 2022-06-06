#include <iostream>
#include <cmath>

#include "mv.h"

using namespace std;

coeff length(MV& mv) {
#pragma gpc begin
    length_mv = mv_from_array(mv);
#pragma clucalc begin
    ? length_sq = length_mv . length_mv;
#pragma clucalc end
    coeff sq;
    sq = mv_get_bladecoeff(length_sq, 1);
    return sqrt(sq);
#pragma gpc end
}

int main() {
    MV a;
    MV b;
    a[1] = 2;
    b[0] = 5;

    MV res = a + b;

    res = res * a;
    res = res * b;

    cout << res[0] << endl;
    cout << res[1] << endl;

    return 0; 
}
