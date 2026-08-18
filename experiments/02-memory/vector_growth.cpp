#include <cstdio>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int N = 10000000;
int g_stack[N];                     // static array acting as a stack

int main() {
  // --- 先看清楚 vector 增长时到底发生了什么 ---
  {
    vector<int> v;
    size_t last = 0; int reallocs = 0; long long copied = 0;
    printf("== vector 增长过程(前 12 次扩容的容量) ==\n  ");
    for (int i = 0; i < N; ++i) {
      v.push_back(i);
      if (v.capacity() != last) {
        if (reallocs < 12) printf("%zu ", v.capacity());
        ++reallocs; copied += last;   // 旧元素全部要搬一遍
        last = v.capacity();
      }
    }
    printf("...\n  共扩容 %d 次，累计搬运了 %lld 个元素(约 %.1f 倍于 N)\n\n",
           reallocs, copied, (double)copied / N);
  }

  auto bench = [](const char* label, auto f) {
    auto t0 = high_resolution_clock::now();
    long long r = f();
    auto t1 = high_resolution_clock::now();
    printf("  %-38s %8.1f ms  (校验 %lld)\n", label,
           duration<double, milli>(t1-t0).count(), r);
  };

  printf("== 往栈里 push %d 个 int ==\n", N);
  bench("1. 静态数组  a[top++]", []{
    int top = 0; for (int i = 0; i < N; ++i) g_stack[top++] = i; return (long long)top; });
  bench("2. vector::push_back (无 reserve)", []{
    vector<int> v; for (int i = 0; i < N; ++i) v.push_back(i); return (long long)v.size(); });
  bench("3. vector::push_back (先 reserve)", []{
    vector<int> v; v.reserve(N); for (int i = 0; i < N; ++i) v.push_back(i); return (long long)v.size(); });

  printf("\n== 同样的事,但元素是 string(拷贝很贵) ==\n");
  const int M = 1000000;
  bench("4. vector<string> (无 reserve)", []{
    vector<string> v; for (int i = 0; i < 1000000; ++i) v.push_back("hello_world_padding");
    return (long long)v.size(); });
  bench("5. vector<string> (先 reserve)", []{
    vector<string> v; v.reserve(1000000);
    for (int i = 0; i < 1000000; ++i) v.push_back("hello_world_padding");
    return (long long)v.size(); });
  return 0;
}
