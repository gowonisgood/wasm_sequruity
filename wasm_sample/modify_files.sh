#!/bin/bash

# 디렉터리 내 모든 파일을 대상으로 작업 수행
for file in $(find . -type f -name "*.c" -o -name "*.cpp" -o -name "*.h"); do
  # 파일에 #ifdef __cplusplus 포함 여부 확인
  if ! grep -q "#ifdef __cplusplus" "$file"; then
    # 파일 맨 앞에 WASM_EXPORT 정의 추가
    echo -e '#ifdef __cplusplus\n#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"\n#else\n#define WASM_EXPORT __attribute__((visibility("default")))\n#endif\n\n' | cat - "$file" > temp && mv temp "$file"
    echo "Added WASM_EXPORT to $file"
  fi

  # int main을 WASM_EXPORT int main으로 바꿔줌
  sed -i 's/\bint main\b/WASM_EXPORT int main/g' "$file"
  echo "Modified main function in $file"
done

