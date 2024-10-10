#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s

#include <string.h>

namespace XXX {
struct YYY {
  static int ZZZ(int x) {
    char array[10];
    memset(array, 0, 10);
    return array[x];  // BOOOM
    // CHECK: ERROR: AddressSanitizer: stack-buffer-overflow
    // CHECK: READ of size 1 at
    // CHECK: is located in stack of thread T0 at offset
    // CHECK: XXX::YYY::ZZZ
  }
};
}  // namespace XXX

WASM_EXPORT int main(int argc, char **argv) {
  int res = XXX::YYY::ZZZ(2 + 10); //hard coding 
  return res;
}
