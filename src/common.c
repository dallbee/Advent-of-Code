#include "common.h"
#include <klib/kvec.h>
#include <sds/sds.h>

sds sdsvec_join(sdsvec input) {
  size_t size = kv_size(input);
  sds s = sdsempty();
  for (size_t i = 0; i < size; ++i)
    s = sdscatsds(s, sdstrim(kv_A(input, i), "\r\n"));
  return s;
}
