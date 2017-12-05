#include <stdbool.h>
#include <klib/khash.h>
#include <klib/kvec.h>
#include <sds/sds.h>
#include "../common.h"

static bool valid_passphrase(sds s) {
    int count;
    sds *tokens = sdssplitargs(s, &count);

    // for small n, arrays are faster than any other structure
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            int len_i = sdslen(tokens[i]);
            int len_j = sdslen(tokens[j]);
            if (!strncmp(tokens[i], tokens[j], max(len_i, len_j))) {
                sdsfreesplitres(tokens, count);
                return false;
            }
        }
    }
    sdsfreesplitres(tokens, count);
    return true;
}

sds solve_04_a(sdsvec input) {
    int sum = 0;
    size_t size = kv_size(input);
    for (size_t i = 0; i < size; ++i) {
        if (valid_passphrase(kv_A(input, i)))
            sum += 1;
    }
    return sdsfromlonglong(sum);
}

sds solve_04_b(sdsvec input) {
    return sdsempty();
}
