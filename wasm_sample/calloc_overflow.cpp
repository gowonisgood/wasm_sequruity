// RUN: %clangxx_asan -O0 %s -o %t
// RUN: %env_asan_opts=allocator_may_return_null=0 not %run %t 2>&1 | FileCheck %s
// RUN: %env_asan_opts=allocator_may_return_null=1 %run %t 2>&1 | FileCheck %s --check-prefix=CHECK-NULL

// REQUIRES: stable-runtime

#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif



WASM_EXPORT int main() {
  void *p = calloc(-1, 1000);
  // CHECK: {{ERROR: AddressSanitizer: calloc parameters overflow: count \* size \(.* \* 1000\) cannot be represented in type size_t}}
  // CHECK: {{#0 0x.* in .*calloc}}
  // CHECK: {{#[1-3] 0x.* in main .*calloc-overflow.cpp:}}[[@LINE-3]]
  // CHECK: SUMMARY: AddressSanitizer: calloc-overflow

  printf("calloc returned: %zu\n", (size_t)p);
  // CHECK-NULL: calloc returned: 0

  return 0;
}
