#include<stdio.h>
int main(){
    int x;
    int y;
    scanf("%d%d",&x,&y);

    printf("0x%08x",!!x);
    return 0;
}