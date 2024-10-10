// RUN: %clangxx_asan -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s



#ifdef __cplusplus
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif



namespace XXX {
class YYY {
 public:
  static char ZZZ[];
};
char YYY::ZZZ[] = "abc";
}

WASM_EXPORT int main(int argc, char **argv) {
  return (int)XXX::YYY::ZZZ[argc + 5];  // BOOM
  // CHECK: {{READ of size 1 at 0x.*}}
  // CHECK: {{0x.* is located 2 bytes after global variable}}
  // CHECK: '{{.*}}XXX::YYY::ZZZ{{.*}}' {{.*}} of size 4
  // CHECK: '{{.*}}XXX::YYY::ZZZ{{.*}}' is ascii string 'abc'
}
