// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O2 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O3 %s -o %t && not %run %t 2>&1 | FileCheck %s

#include <string.h>
#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif
WASM_EXPORT WASM_EXPORT int main(int argc, char **argv) {
  char x[10];
  memset(x, 0, 10);
  int res = x[2 * 10];  // BOOOM
  // CHECK: {{READ of size 1 at 0x.* thread T0}}
  // CHECK: {{    #0 0x.* in main .*stack-buffer-overflow.cpp:}}[[@LINE-2]]
  // CHECK: {{Address 0x.* is located in stack of thread T0 at offset}}
  // CHECK-NEXT: in{{.*}}main{{.*}}stack-buffer-overflow.cpp
  return res;
}
