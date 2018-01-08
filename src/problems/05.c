#include "../common.h"
#include <klib/kvec.h>
#include <sds/sds.h>
#include <stdbool.h>
#include <stdlib.h>

int cpu(sdsvec input, bool decrement) {
  kvec_t(sds) data;
  kv_init(data);
  kv_copy(sds, data, input);

  int end = kv_size(data) - 1;
  int pos = 0, jump = 0, count = 0;

  while (pos >= 0 && pos < end) {
    jump = atoi(kv_A(data, pos));
    if (decrement && jump >= 3) {
      kv_A(data, pos) = sdsfromlonglong(jump - 1);
    } else {
      kv_A(data, pos) = sdsfromlonglong(jump + 1);
    }
    pos += jump;
    ++count;
  }

  kv_destroy(data);
  return count;
}

sds solve_05_a(sdsvec input) { return sdsfromlonglong(cpu(input, false)); }

sds solve_05_b(sdsvec input) { return sdsfromlonglong(cpu(input, true)); }
