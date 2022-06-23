#include "clock.h"

#include <time.h>

double current_time() {
    double x = clock();
    return x / (double) CLOCKS_PER_SEC;
}
