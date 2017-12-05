#include <stdlib.h>
#include <klib/kvec.h>
#include <sds/sds.h>
#include "../common.h"

sds solve_03_a(sdsvec input) {
    int num = atoi(kv_A(input, 0));

    // Reach nearest perfect square
    int i;
    for (i = 1; i*i < num; i += 2);

    // Find distances based on pivots
    int d;
    for (int j = 0; j < 4; ++j) {
        int pivot = i*i - j*(i-1);
        d = abs(pivot - num);
        if (d <= (i-1) / 2) {
            return sdsfromlonglong(i-1-d);
        }
    }

    return sdsempty();
}

sds solve_03_b(sdsvec input) {
    return sdsempty();
}
