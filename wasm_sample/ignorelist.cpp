// Test the ignorelist functionality of ASan

// RUN: echo "fun:*brokenFunction*" > %tmp
// RUN: echo "global:*badGlobal*" >> %tmp
// RUN: echo "src:*ignorelist-extra.cpp" >> %tmp
// RUN: %clangxx_asan -fsanitize-ignorelist=%tmp -O0 %s -o %t \
// RUN: %p/Helpers/ignorelist-extra.cpp && %run %t 2>&1
// RUN: %clangxx_asan -fsanitize-ignorelist=%tmp -O1 %s -o %t \
// RUN: %p/Helpers/ignorelist-extra.cpp && %run %t 2>&1
// RUN: %clangxx_asan -fsanitize-ignorelist=%tmp -O2 %s -o %t \
// RUN: %p/Helpers/ignorelist-extra.cpp && %run %t 2>&1
// RUN: %clangxx_asan -fsanitize-ignorelist=%tmp -O3 %s -o %t \
// RUN: %p/Helpers/ignorelist-extra.cpp && %run %t 2>&1

// badGlobal is accessed improperly, but we ignorelisted it. Align
// it to make sure memory past the end of badGlobal will be in
// the same page.
#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


__attribute__((aligned(16))) int badGlobal;
int readBadGlobal() {
  return (&badGlobal)[1];
}

// A function which is broken, but excluded in the ignorelist.
int brokenFunction(int argc) {
  char x[10] = {0};
  return x[argc * 10];  // BOOM
}

// This function is defined in Helpers/ignorelist-extra.cpp, a source file which
// is ignorelisted by name
int externalBrokenFunction(int argc){
  char x[10] = {0};
  return x[argc * 10];  // BOOM
}

WASM_EXPORT int main(int argc, char **argv) {
  brokenFunction(argc);
  int x = readBadGlobal();
  externalBrokenFunction(argc);
  return 0;
}
