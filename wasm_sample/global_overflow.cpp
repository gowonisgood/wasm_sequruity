
// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O2 %s -o %t && not %run %t 2>&1 | FileCheck %s
// RUN: %clangxx_asan -O3 %s -o %t && not %run %t 2>&1 | FileCheck %s

// Issue #108194: Incomplete .debug_line at -O1 and above.
// XFAIL: target={{.*sparc.*}}
#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

#include <string.h>
WASM_EXPORT WASM_EXPORT int main(int argc, char **argv) {
  static char XXX[10];
  static char YYY[10];
  static char ZZZ[10];
  memset(XXX, 0, 10);
  memset(YYY, 0, 10);
  memset(ZZZ, 0, 10);
  int res = YYY[2 * 10];  // BOOOM
  // CHECK: {{READ of size 1 at 0x.* thread T0}}
  // CHECK: {{    #0 0x.* in main .*global-overflow.cpp:}}[[@LINE-2]]
  // CHECK: {{0x.* is located 0 bytes after global variable}}
  // CHECK:   {{.*YYY.* of size 10}}
  res += XXX[argc] + ZZZ[argc];
  return res;
}
