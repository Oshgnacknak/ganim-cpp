#include "clock.h"

#include <time.h>

double current_time() {
    auto x = clock();
    return x / CLOCKS_PER_SEC;
}
