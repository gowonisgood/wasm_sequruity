#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s

// Test the time() interceptor.

// FIXME: There's no interceptor for time() on Windows yet.
// XFAIL: target={{.*windows-(msvc.*|gnu)}}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

WASM_EXPORT int main() {
  time_t *tm = (time_t*)malloc(sizeof(time_t));
  free(tm);
  time_t t = time(tm);
  printf("Time: %s\n", ctime(&t));
  // CHECK: use-after-free
  // Regression check for
  // https://code.google.com/p/address-sanitizer/issues/detail?id=321
  // CHECK: SUMMARY
  return 0;
}
