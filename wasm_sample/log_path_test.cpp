#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

WASM_EXPORT int main(int argc, char **argv) {
  //if (argc > 2) return 0;
  char *x = (char*)malloc(10);
  memset(x, 0, 10);
  int res = x[2 * 10];  // BOOOM set 2 hard coding GO
  free(x);
  return res;
}
