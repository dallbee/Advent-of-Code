#include <klib/kvec.h>
#include <sds/sds.h>
#include "common.h"

static sds inverse_captcha(sdsvec input, int mod_divisor) {
    sds s = sdsvec_join(input);
    size_t len = sdslen(s);
    int count = 0;

    for (size_t i = 0; i < len; ++i) {
        if (s[i] == s[(i+1) % (len / mod_divisor)]) {
            count += s[i] - '0';
        }
    }

    sdsfree(s);
    return sdscatfmt(sdsempty(), "%i", count);
}

sds solve_01_a(sdsvec input) {
    return inverse_captcha(input, 1);
}

sds solve_01_b(sdsvec input) {
    return inverse_captcha(input, 2);
}
