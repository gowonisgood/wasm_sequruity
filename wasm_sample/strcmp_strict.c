#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


// Test strict_string_checks option in strcmp function
// RUN: %clang_asan %s -o %t && %run %t 2>&1
// RUN: %env_asan_opts=strict_string_checks=false %run %t 2>&1
// RUN: %env_asan_opts=strict_string_checks=true not %run %t 2>&1 | FileCheck %s

//#include <assert.h>
#include <stdlib.h>
#include <string.h>

WASM_EXPORT int main(int argc, char **argv) {
  size_t size = 100;
  char fill = 'o';
  char *s1 = (char*)malloc(size);
  memset(s1, fill, size);
  char *s2 = (char*)malloc(size);
  memset(s2, fill, size);
  s1[size - 1] = 'z';
  s2[size - 1] = 'x';
  int r = strcmp(s1, s2);
  // CHECK: {{.*ERROR: AddressSanitizer: heap-buffer-overflow on address}}
  // CHECK: READ of size 101
  //assert(r == 1);
  free(s1);
  free(s2);
  return 0;
}
