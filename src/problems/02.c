#include "../common.h"
#include <klib/kvec.h>
#include <limits.h>
#include <sds/sds.h>
#include <stdlib.h>

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

static int row_quotient(sds row) {
  int count;
  sds *tokens = sdssplitargs(row, &count);
  int quotient = 0;
  for (int i = 0; i < count - 1; ++i) {
    int a = atoi(tokens[i]);
    for (int j = i + 1; j < count; ++j) {
      int b = atoi(tokens[j]);
      if (max(a, b) % min(a, b) == 0) {
        quotient = max(a, b) / min(a, b);
        goto cleanup;
      }
    }
  }

cleanup:
  sdsfreesplitres(tokens, count);
  return quotient;
}

sds solve_02_a(sdsvec input) {
  int checksum = 0;
  size_t size = kv_size(input);
  for (size_t i = 0; i < size; ++i) {
    checksum += row_difference(kv_A(input, i));
  }
  return sdsfromlonglong(checksum);
}

sds solve_02_b(sdsvec input) {
  int checksum = 0;
  size_t size = kv_size(input);
  for (size_t i = 0; i < size; ++i) {
    checksum += row_quotient(kv_A(input, i));
  }
  return sdsfromlonglong(checksum);
}
