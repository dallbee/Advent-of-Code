#include <stdbool.h>
#include <klib/khash.h>
#include <klib/kvec.h>
#include <sds/sds.h>
#include "../common.h"

static int compare(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

static bool is_anagram(sds a, sds b) {
    if (sdslen(a) != sdslen(b))
        return false;
    qsort(a, sdslen(a), sizeof(char), compare);
    qsort(b, sdslen(b), sizeof(char), compare);
    return !((bool)strncmp(a, b, sdslen(a)));
}

static bool valid_passphrase(sds s, bool check_anagram) {
    int count;
    sds *tokens = sdssplitargs(s, &count);

    bool valid = true;

    // for small n, arrays are faster than any other structure
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            int len_i = sdslen(tokens[i]);
            int len_j = sdslen(tokens[j]);

            // check for identical words
            if (!strncmp(tokens[i], tokens[j], max(len_i, len_j))) {
                valid = false;
                goto cleanup;
            }

            // check for anagrams
            if (check_anagram && is_anagram(tokens[i], tokens[j])) {
                valid = false;
                goto cleanup;
            }
        }
    }

cleanup:
    sdsfreesplitres(tokens, count);
    return valid;
}

sds solve_04_a(sdsvec input) {
    int sum = 0;
    size_t size = kv_size(input);
    for (size_t i = 0; i < size; ++i) {
        if (valid_passphrase(kv_A(input, i), false))
            sum += 1;
    }
    return sdsfromlonglong(sum);
}

sds solve_04_b(sdsvec input) {
    int sum = 0;
    size_t size = kv_size(input);
    for (size_t i = 0; i < size; ++i) {
        if (valid_passphrase(kv_A(input, i), true))
            sum += 1;
    }
    return sdsfromlonglong(sum);
}
