// Regression test for
// https://code.google.com/p/address-sanitizer/issues/detail?id=183

// RUN: %clangxx_asan -O2 %s -o %t
// RUN: not %run %t 12 2>&1 | FileCheck %s
// RUN: not %run %t 100 2>&1 | FileCheck %s
// RUN: not %run %t 10000 2>&1 | FileCheck %s

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

WASM_EXPORT WASM_EXPORT int main(int argc, char *argv[]) {
  fprintf(stderr, "main\n");
  int *x = new int[5];
  memset(x, 0, sizeof(x[0]) * 5);
  int index = atoi(argv[1]);
  unsigned res = x[index];
  // CHECK: main
  // CHECK-NOT: CHECK failed
  delete[] x;
  return (res % 10) + 1;
}
