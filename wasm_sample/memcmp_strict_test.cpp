#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif



WASM_EXPORT int main() {
  char kFoo[] = "foo";
  char kFubar[] = "fubar";
  int res = memcmp(kFoo, kFubar, strlen(kFubar));
  printf("res: %d\n", res);
  // CHECK: AddressSanitizer: stack-buffer-overflow
  return 0;
}
