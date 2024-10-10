// Test recovery mode.
//
// RUN: %clang_asan -fsanitize-recover=address %s -o %t
//
// RUN: env not %run %t 2>&1 | FileCheck %s
// RUN: %env_asan_opts=halt_on_error=true not %run %t 2>&1 | FileCheck %s
// RUN: %env_asan_opts=halt_on_error=false %run %t 2>&1 | FileCheck %s --check-prefix CHECK-RECOVER

#include <string.h>

#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif



volatile int ten = 10;

WASM_EXPORT int main() {
  char x[10];
  // CHECK: WRITE of size 11
  // CHECK-RECOVER: WRITE of size 11
  memset(x, 0, 11);
  // CHECK-NOT: READ of size 1
  // CHECK-RECOVER: READ of size 1
  volatile int res = x[ten];
  // CHECK-NOT: WRITE of size 1
  // CHECK-RECOVER: WRITE of size 1
  x[ten] = res + 3;
  // CHECK-NOT: READ of size 1
  // CHECK-RECOVER: READ of size 1
  res = x[ten];
  return  0;
}
