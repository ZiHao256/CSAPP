#include<stdio.h>
int main(){
    int x;
    scanf("%x",&x);
    // printf("0x%08x, %d",(x|(~x+1))>>31,(x|(~x+1))>>31);
    printf("%08x",x>>31);

    return 0;
}