#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif


// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s

struct IntHolder {
  __attribute__((noinline)) const IntHolder &Self() const {
    return *this;
  }
  int val = 3;
};

const IntHolder *saved;

WASM_EXPORT int main(int argc, char *argv[]) {
  saved = &IntHolder().Self();
  int x = saved->val;  // BOOM
  // CHECK: ERROR: AddressSanitizer: stack-use-after-scope
  // CHECK:  #0 0x{{.*}} in main {{.*}}use-after-scope-temp2.cpp:[[@LINE-2]]
  return x;
}
