#include <cstdio>
#include <climits>

// volatile 防止编译器在编译期直接把结果算出来
volatile int sink;

int main() {
  int x = INT_MAX - 2;
  printf("从 INT_MAX-2 开始，一次加 1：\n");
  for (int i = 0; i < 5; ++i) {
    printf("  x = %11d   (十六进制 0x%08X)\n", x, (unsigned)x);
    sink = x;
    x = x + 1;
  }
  return 0;
}
