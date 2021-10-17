#include<stdio.h>

int add(int x, int y){
    int sum = x;
    int carry = y;

    while(carry!=0){
        int t = sum;
        sum = t ^ carry;
        carry = (t&carry) <<1;
    }
    return sum;
}
int main(){
    int x,y;
    scanf("%d,%d",&x,&y);
    printf("%d",add(x,y));
    return 0;
}