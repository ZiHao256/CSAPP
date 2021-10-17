#include<stdio.h>
int main(){
    unsigned uf = 0x7f800000;
//    scanf("%x",&uf);
    unsigned s = (uf>>31)&(0x1);
    unsigned e = (uf>>23)&(0xff);
    int m = (uf)&(0x7fffff);
    unsigned ans=0;
    //printf("%08x %08x %08x\n",s,e,m);
    

    if(e == 0){
        ans = 0;
    }else if(e == 0xff){
        ans = 0x80000000;
    }else{
        m = m | (0x800000);
        int l = e-(127);
        printf("%x\n",m);
        if(l>=0 && l<=23){
            m = m >>(24-l-1);
            // printf("%x\n",m);
        }else if(l>23 && l<=31){
            m = m<<(l-23);
        }else if(l >31){
          m = 0x80000000;
        }else if(l<0){
          m = 0;
        }

        if(s){
            ans = -m;
        }else{
            ans = m;
        }

    }
    printf("0x%08x %d\n",ans,ans);

    return 0;
}