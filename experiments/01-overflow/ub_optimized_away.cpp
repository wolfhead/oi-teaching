#include <cstdio>
#include <climits>

// "如果 x 加 1 之后反而变小了,说明溢出了" —— 一个看起来很合理的检查
bool did_it_overflow(int x) { return x + 1 < x; }

int main() {
  printf("did_it_overflow(INT_MAX) = %s\n",
         did_it_overflow(INT_MAX) ? "true" : "false");
  return 0;
}
