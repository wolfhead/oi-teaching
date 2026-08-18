#include <cstdio>
volatile long d = 0;
void dfs(){                      // 模拟真实 DFS：带几个局部变量
    int vis[20]; int u,v,w,cnt;  // 约 100 字节的栈帧
    vis[0]=1; u=v=w=cnt=0;
    ++d; if(d%50000==0){printf("%ld\n",d);fflush(stdout);}
    dfs();
}
int main(){ dfs(); return 0; }
