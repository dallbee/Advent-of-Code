#include <limits.h>
#include <stdlib.h>
#include <klib/kvec.h>
#include <sds/sds.h>
#include "../common.h"

static int row_difference(sds row) {
    int count;
    sds *tokens = sdssplitargs(row, &count);

    int small = INT_MAX;
    int large = INT_MIN;
    for (int i = 0; i < count; ++i) {
        int value = atoi(tokens[i]);
        small = min(small, value);
        large = max(large, value);
    }

    sdsfreesplitres(tokens, count);
    return large - small;
}

sds solve_02_a(sdsvec input) {
    int checksum = 0;
    for (size_t i = 0; i < kv_size(input); ++i) {
        checksum += row_difference(kv_A(input, i));
        printf("checksum: %d\n", checksum);
    }
    return sdsfromlonglong(checksum);
}

sds solve_02_b(sdsvec input) {
    return sdsempty();
}
