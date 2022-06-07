#include <iostream>
#include <cmath>

#include "mv.h"

using namespace std;

int main() {
    MV a = vector(1, 1, 1);
    a *= 5.5 / sqrt(3);
    
    cout << length(a) << endl;

    return 0; 
}
