// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s

// Test the frexp() interceptor.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


WASM_EXPORT int main() {
  double x = 3.14;
  int *exp = (int*)malloc(sizeof(int));
  free(exp);
  double y = frexp(x, exp);
  // CHECK: use-after-free
  // CHECK: SUMMARY
  return 0;
}
