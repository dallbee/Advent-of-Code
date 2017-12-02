#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <klib/kvec.h>
#include <sds/sds.h>

// Math definitions
#define abs(a) (((a) > 0) ? (a) : -(a)) min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) < (b)) ? (b) : (a))

// Array count
#define count(array) (sizeof(array) / sizeof(array[0]))

// Performance macros
#define ALWAYS_INLINE inline __attribute__((always_inline))
#define LIKELY_IS(x, y) __builtin_expect((x), (y))
#define LIKELY(x) LIKELY_IS(!!(x), 1)
#define UNLIKELY(x) LIKELY_IS((x), 0)

typedef kvec_t(sds) sdsvec;
typedef sds (*solver_t)(sdsvec);

sds sdsvec_join(sdsvec);

sds solve_01_a(sdsvec);
sds solve_01_b(sdsvec);
sds solve_02_a(sdsvec);
sds solve_02_b(sdsvec);
sds solve_03_a(sdsvec);
sds solve_03_b(sdsvec);
sds solve_04_a(sdsvec);
sds solve_04_b(sdsvec);
sds solve_05_a(sdsvec);
sds solve_05_b(sdsvec);
sds solve_06_a(sdsvec);
sds solve_06_b(sdsvec);
sds solve_07_a(sdsvec);
sds solve_07_b(sdsvec);
sds solve_08_a(sdsvec);
sds solve_08_b(sdsvec);
sds solve_09_a(sdsvec);
sds solve_09_b(sdsvec);
sds solve_10_a(sdsvec);
sds solve_10_b(sdsvec);
sds solve_11_a(sdsvec);
sds solve_11_b(sdsvec);
sds solve_12_a(sdsvec);
sds solve_12_b(sdsvec);
sds solve_13_a(sdsvec);
sds solve_13_b(sdsvec);
sds solve_14_a(sdsvec);
sds solve_14_b(sdsvec);
sds solve_15_a(sdsvec);
sds solve_15_b(sdsvec);
sds solve_16_a(sdsvec);
sds solve_16_b(sdsvec);
sds solve_17_a(sdsvec);
sds solve_17_b(sdsvec);
sds solve_18_a(sdsvec);
sds solve_18_b(sdsvec);
sds solve_19_a(sdsvec);
sds solve_19_b(sdsvec);
sds solve_20_a(sdsvec);
sds solve_20_b(sdsvec);
sds solve_21_a(sdsvec);
sds solve_21_b(sdsvec);
sds solve_22_a(sdsvec);
sds solve_22_b(sdsvec);
sds solve_23_a(sdsvec);
sds solve_23_b(sdsvec);
sds solve_24_a(sdsvec);
sds solve_24_b(sdsvec);
sds solve_25_a(sdsvec);
sds solve_25_b(sdsvec);
