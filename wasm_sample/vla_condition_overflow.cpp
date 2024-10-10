// RUN: %clangxx_asan -O0 -mllvm -asan-instrument-dynamic-allocas %s -o %t
// RUN: not %run %t 2>&1 | FileCheck %s
//
// REQUIRES: stable-runtime

//#include <assert.h>
#include <stdint.h>


#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif



__attribute__((noinline)) void foo(int index, int len) {
  if (index > len) {
    char str[len];
    //assert(!(reinterpret_cast<uintptr_t>(str) & 31L));
    str[index] = '1'; // BOOM
// CHECK: ERROR: AddressSanitizer: dynamic-stack-buffer-overflow on address [[ADDR:0x[0-9a-f]+]]
// CHECK: WRITE of size 1 at [[ADDR]] thread T0
  }
}

WASM_EXPORT int main(int argc, char **argv) {
  foo(33, 10);
  return 0;
}
