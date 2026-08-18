#include <cstdio>
volatile long d = 0;
void f(){ ++d; if(d%50000==0){printf("%ld\n",d);fflush(stdout);} f(); }
int main(){ f(); return 0; }
