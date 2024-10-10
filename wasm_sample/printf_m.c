// RUN: %clang_asan -O2 %s -o %t && %run %t

// FIXME: printf is not intercepted on Windows yet.
// UNSUPPORTED: target={{.*windows-msvc.*}}

#include <stdio.h>

#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif



WASM_EXPORT int main() {
  char s[5] = {'w', 'o', 'r', 'l', 'd'};
  // Test that %m does not consume an argument. If it does, %s would apply to
  // the 5-character buffer, resulting in a stack-buffer-overflow report.
  printf("%m %s, %.5s\n", "hello", s);
  return 0;
}
