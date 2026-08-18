#include <cstdio>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int N = 5000000;
int g_arr[N];                       // 1. static global array

struct Node { int val; Node* nxt; };

template<class F> double timeit(F f, const char* label, long long& out) {
  auto t0 = high_resolution_clock::now();
  out = f();
  auto t1 = high_resolution_clock::now();
  double ms = duration<double, milli>(t1 - t0).count();
  printf("  %-34s %8.1f ms   (sum=%lld)\n", label, ms, out);
  return ms;
}

int main() {
  long long s;
  for (int i = 0; i < N; ++i) g_arr[i] = i & 7;

  printf("== 遍历 %d 个 int 求和,四种内存布局 ==\n\n", N);

  double t1 = timeit([&]{ long long a=0; for(int i=0;i<N;++i) a+=g_arr[i]; return a; },
                     "1. 静态全局数组", s);

  int* d = new int[N];
  for (int i = 0; i < N; ++i) d[i] = i & 7;
  double t2 = timeit([&]{ long long a=0; for(int i=0;i<N;++i) a+=d[i]; return a; },
                     "2. new 一次的动态数组", s);

  // 3. 指针链表,节点按分配顺序链接(内存基本连续)
  vector<Node*> nodes(N);
  for (int i = 0; i < N; ++i) { nodes[i] = new Node{i & 7, nullptr}; }
  for (int i = 0; i + 1 < N; ++i) nodes[i]->nxt = nodes[i+1];
  nodes[N-1]->nxt = nullptr;
  double t3 = timeit([&]{ long long a=0; for(Node*p=nodes[0];p;p=p->nxt) a+=p->val; return a; },
                     "3. 指针链表(顺序分配)", s);

  // 4. 同样的节点,但链接顺序打乱 -> 模拟真实碎片化
  vector<Node*> sh = nodes;
  mt19937 rng(12345);
  shuffle(sh.begin(), sh.end(), rng);
  for (int i = 0; i + 1 < N; ++i) sh[i]->nxt = sh[i+1];
  sh[N-1]->nxt = nullptr;
  double t4 = timeit([&]{ long long a=0; for(Node*p=sh[0];p;p=p->nxt) a+=p->val; return a; },
                     "4. 指针链表(打乱=真实场景)", s);

  printf("\n  相对静态数组:  动态数组 %.2fx   顺序链表 %.2fx   打乱链表 %.2fx\n",
         t2/t1, t3/t1, t4/t1);
  return 0;
}
