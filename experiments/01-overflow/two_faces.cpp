#include <cstdio>
#include <climits>

__attribute__((noinline))
void probe(int x) {
  int y = x + 1;                       // x 是 INT_MAX,这里溢出
  printf("  x         = %d\n", x);
  printf("  y = x + 1 = %d      <-- y 打印出来是这个\n", y);
  printf("  y > x  ?    %s          <-- 同一个 y,编译器却认为...\n",
         y > x ? "true" : "false");
  printf("  y < 0  ?    %s\n", y < 0 ? "true" : "false");
}

int main(int argc, char**) {
  // 用 argc 构造 INT_MAX,防止编译期常量折叠(正常运行 argc==1)
  probe(INT_MAX - argc + 1);
  return 0;
}
