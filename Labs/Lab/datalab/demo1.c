#include<stdio.h>
int main(){
    int x,y;
    scanf("%d%d",&x,&y);
    int a = ~(x&(~y));
    int b = ~((~x)&y);

    printf("0x%08x",~(a&b));
    return 0;
}