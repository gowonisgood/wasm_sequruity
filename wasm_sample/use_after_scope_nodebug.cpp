#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


// RUN: %clangxx_asan -O1 %s -o %t && %run %t

#include <stdio.h>
#include <stdlib.h>

int *p[3];

WASM_EXPORT int main() {
  // Variable goes in and out of scope.
  for (int i = 0; i < 3; i++) {
    int x;
    p[i] = &x;
  }
  printf("PASSED\n");
  return 0;
}
