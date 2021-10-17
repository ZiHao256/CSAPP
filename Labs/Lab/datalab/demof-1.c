#include<stdio.h>
int main(){
    unsigned uf = 0x800000;

    // float f = 12345.0;
    // unsigned* uf = (unsigned*) &f;

    // printf("输入十六进制数\n");
    // scanf("%x",&uf);
    // unsigned char x = (*uf>>10) &0xf;
    // printf("0x%02x",x);
    printf("0x%08x\n",uf);
    unsigned um = uf & (0x7fffff);
    unsigned ue = (uf>>23) & (0xff);
    unsigned us = (uf>>31) & (0x1);
    ue = ue+1;
    printf("%02x %02x\n",ue,ue);

    unsigned ans = (us<<31) | (ue<<23) | um;

    printf("0x%08x",ans);

    return 0;
}
