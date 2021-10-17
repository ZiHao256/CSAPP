#include<stdio.h>
int main(){
    int x;
    scanf("%x",&x);
    int a = 0xAA;
    a = (a<<8) + a;
    a = (a<<16) + a;
    int b = !((x&a)^a);
    //printf("0x%08x",x);
    printf("%d",b);

    return 0;
}