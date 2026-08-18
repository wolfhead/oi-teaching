#include <cstdio>
int a[3000000];            // 同样 12MB，但开在函数外面（全局/静态区）
int main(){
    a[0] = 1; a[2999999] = 2;
    printf("全局数组：活下来了\n");
    return 0;
}
