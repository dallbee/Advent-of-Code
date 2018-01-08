#include "../common.h"
#include <klib/kvec.h>
#include <sds/sds.h>
#include <stdbool.h>
#include <string.h>

static int reallocate(int *buckets, size_t len) {
  int count = 0;

  // Make sure we have valid input
  if (len <= 0) {
    return count;
  }

  kvec_t(int *) seen;
  kv_init(seen);

  bool found = false;
  while (!found) {
    int *copy = malloc(len * sizeof(*copy));
    memcpy(copy, buckets, len * sizeof(*copy));
    kv_push(int *, seen, copy);

    size_t index = 0;
    for (size_t i = 0; i < len; ++i) {
      if (buckets[i] > buckets[index]) {
        index = i;
      }
    }

    int tmp = buckets[index];
    buckets[index] = 0;

    for (; tmp > 0; --tmp) {
      index = (index + 1) % len;
      buckets[index]++;
    }

    ++count;

    for (size_t i = 0; i < kv_size(seen); ++i) {
      if (!memcmp(buckets, kv_A(seen, i), len * sizeof(*buckets))) {
        found = true;
        break;
      }
    }
  }

  for (size_t i = 0; i < kv_size(seen); ++i) {
    free(kv_A(seen, i));
  }

  kv_destroy(seen);
  return count;
}

static sds get_count(sds s, bool rotation) {
  int len;
  sds *tokens = sdssplitargs(s, &len);

  int *buckets = malloc(len * sizeof(*buckets));
  for (int i = 0; i < len; ++i) {
    buckets[i] = atoi(tokens[i]);
  }

  int count = reallocate(buckets, len);
  if (rotation) {
    count = reallocate(buckets, len);
  }

  free(buckets);
  sdsfreesplitres(tokens, len);
  return sdsfromlonglong(count);
}

sds solve_06_a(sdsvec input) { return get_count(kv_A(input, 0), false); }

sds solve_06_b(sdsvec input) { return get_count(kv_A(input, 0), true); }
