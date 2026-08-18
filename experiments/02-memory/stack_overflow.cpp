#include <cstdio>
int main(){
    int a[3000000];        // 12MB 开在 main 里面（栈上）
    a[0] = 1; a[2999999] = 2;
    printf("局部数组：活下来了\n");
    return 0;
}
