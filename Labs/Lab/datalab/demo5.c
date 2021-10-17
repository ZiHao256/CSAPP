#include<stdio.h>
int main(){
    int x;
    scanf("%x",&x);

    printf("0x%08x %d",~x+1,~x+1);

    return 0;
}