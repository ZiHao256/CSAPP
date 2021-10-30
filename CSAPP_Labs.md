---
title: CSAPP Labs
author: ALex Ma
---

[toc]

[Lab参考]([CSAPP-Lab - 知乎 (zhihu.com)](https://www.zhihu.com/column/c_1325107476128473088))

# 0 配置实验环境

**目的**：在本机的编译器编写我们的代码。然后在 docker 中的虚拟容器上编译和运行我们的代码

[参考](https://zhuanlan.zhihu.com/p/148511634)

## 1 windows10 启用 WSL2

[启用WSL2]([(42条消息) Win10家庭版安装WSL2和docker_xzlzx-CSDN博客](https://blog.csdn.net/qq_41101344/article/details/108828799))

启用WSL和虚拟化技术



## 2 下载安装 配置Ubuntu 发行版

1.从 Microsoft Store 下载

注意需禁用旧的命令行

2.更换下载源为阿里云并更新



## 3 将 WSL 1 上的 Ubuntu 转换到 WSL 2

`wsl --set-version Ubuntu-20.04 2`



## 4 安装 Docker

采用 Docker Desktop for windows方式：

**Docker Desktop 4.0.1**

* [软连接至D盘]([(42条消息) windows10 docker 安装在D盘_凉-CSDN博客_docker安装到d盘](https://blog.csdn.net/liangcsdn111/article/details/110236655))

![在这里插入图片描述](E:\2nd_summer_holiday\CSAPP\CSAPP_Labs.assets\20201127170053920.png)

https://zhuanlan.zhihu.com/p/148511634)

## 5 配置docker

1. 使得通过WSL2访问 docker desktop for windows

[参考](https://zhuanlan.zhihu.com/p/148511634)

2. 配置镜像



## 6 创建实验容器

1. 下载并解压tar文件

2. 创建容器并挂载目录：[CSAPP实验环境搭建_博客-CSDN博客_csapp实验环境搭建](https://blog.csdn.net/aawoe/article/details/107104947)

   1. `docker container run -it -v /mnt/e/2nd_summer_holiday/CSAPP/Labs/Lab:/csapp --name=csapp_env ubuntu /bin/bash`
1. [关于Docker目录挂载的总结 - iVictor - 博客园 (cnblogs.com)](https://www.cnblogs.com/ivictor/p/4834864.html)
      2. ==注意==：windows的ubuntu子系统安装后的文件目录路径在`/mnt/e...`

   2. 冒号前注意绝对路径的写法，或者使用双引号包裹windows下的绝对路径

   3. 从该ubuntu镜像创建容器，命名为csapp_env，且挂载csapp共享文件夹(对应容器根目录下的csapp文件夹)，之前下载的lab资源通过该文件夹和容器共享


==**注意**==：挂载后，发现容器内对应的文件夹内，文件不完整

**分析**：和子系统的`/mnt/`路径有关？

**答**：[ Windows的Ubuntu子系统安装后的文件目录所在路径_Linux I Tell U-CSDN博客](https://blog.csdn.net/no1xium/article/details/107695575)

*# windows10的硬盘都在 /mnt 目录下* cd /mnt *# 查看目录就可以看到盘符*

## 7 启动或退出环境

* 重新运行容器实例
  `docker container start csapp_env`
* 进入容器并打开bash
  `docker container exec -it csapp_env /bin/bash`
* 退出环境
  `CTRL+D或者使用exit命令即可从容器中退出`
* 停止容器
  当不需要进行实验时使用kill命令终止实例的运行并释放系统资源
  `docker container kill csapp_env`



## 8 配置编译环境

* 安装 vim和gedit编辑器

  `apt install vim`

  `apt install gedit`

* 更换国内源

  [Windows10子系统Ubuntu18.04LTS更换国内源](https://blog.csdn.net/weixin_41884010/article/details/97898108)

* 更新 apt 源
  `apt -y update`
* 安装`sudo`
  `apt install sudo`
* 安装c/c++编译环境
  `apt install make automake gcc gcc-c++ kernel-devel`
* 安装gdb
  `apt install gdb`

# 1 DataLab

* 读完了第一二章内容

[参考](https://zhuanlan.zhihu.com/p/82529114)

## 1 阅读 `readme` 完成配置

![image-20210925094449699](E:\2nd_summer_holiday\CSAPP\CSAPP_Labs.assets\image-20210925094449699.png)

1. 阅读`bits.c`的注释与代码，并编辑
2. 命令行运行`./dlc -e bits.c`查看自己用了多少操作符，以及是否有代码风格问题
3. 运行`make clean && make btest`编译文件
4. 运行`./btest`检查自己是否做对了
5. return 1 直到全部做完
6. 最终运行`./driver.pl`获得打分

==注意==：由于Lab的目标程序是32位程序，在64位机器上构建会出现问题。

`make`后：

![image-20210925094923789](E:\2nd_summer_holiday\CSAPP\CSAPP_Labs.assets\image-20210925094923789.png)

==解决方案==：[参考](https://zhuanlan.zhihu.com/p/82529114)

* 运行`apt-get installbuild-essential module-assistant gcc-multilib g++-multilib` 或者 `yum install glibc-devel.i686 libstdc++-devel.i686`

> 这是因为 makefile 里它的目标文件是32位的，64位机器上没办法直接直接编译目标为32位的程序文件，会抛缺少对应的库

一切准备就绪，开始阅读`bits.c`注释完成任务！

## 2 *INTEGER CODING*

1.`bitXor(int x, int y)`

要求：

```
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
```

分析：

`x^y = ~x&y + x&(~y) = ~(~(x&(~y)) & ~(~x&y))`

```C
int bitXor(int x, int y) {
  int a = ~(x&(~y));
  int b = ~((~x)&y);
  return ~(a&b);
}
```



2.`tmin(void)`

要求：

```
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
```



分析：

返回int类型的最小补码

负权位为1，其余为0时最小

可以将1左移31位

```C
int tmin(void) {
  return 1<<31;
}
```



3.`isTmax(int x)`

要求：

```
/*
 * isTmax - returns 1 if x is the maximum two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
```



* `x is maximum two's complement ? 1 : 0`

即是否为：`0x7fff ffff`

可以利用**如下性质**：

* 最大补码+1溢出为负数(最小补码)，最大补码+最小补码等于 -1，-1再加1变为int无法表示，从而变为0。
* C中`!0`为1，`!`负数或整数都为0

`./btest`后：`0xffff ffff`不符合

特判：[参考]([CSAPP:Lab1 -DataLab 超详解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/339047608))

* 可以看到`0xffff ffff` +1为0
* !!(`0xffff ffff` +1)  为0，与该特例中上式`&`可以得到0，而其他情况`&`正常运算

```C
int isTmax(int x) {  
  int a = x+1;    //is Tmin?
  int b = a+x;    //is -1?
  return !(b+1) & (!!(x+1));
}
```

另一种方式

> 自己与自己异或会得到0，也就是说我们可以用异或来判断等于`!((~(x+1)^x))` 判断这个是否为1即可判断是否为最大值

但也要考虑特例`-1`,代码如下：

```C
int isTmax(int x) {  
  int a = x+1;    //is Tmin?
  int b = ~a;    //is -1?
  return !(b^x) & (!!(x+1));
}
```



4. `allOddBits(int x)`

**要求**：

```
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
```

**分析**：只需要判断 `0xAAAA AAAA`&`x` 的结果是否为`0xAAAA AAAA`

* 小技巧：`=` 可以使用 `!(a^b)` 代替
* 而由于规定只能定义`0-255(0xff)`，不能直接定义`0xAAAA AAAA`
* 可以先定义`oxAA`，再使用移位运算符`<<`
  * 注意移位运算优先级，低于+

```C
int allOddBits(int x) {
  int a = 0xaa;
  a = (a<<8) + a;
  a = (a<<16) + a;
  return !( (a)^(a&x) );
}
```



5.`int negate(int x)`

**要求**：

```
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
```

**分析：**分析易得到一个性质

`x + ~x = -1`

```C
int negate(int x) {
  return (~x + 1);
}
```



6.`int isAsciiDigit(int x)`

要求：

```
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
```

分析：

`0011 0000 - 0011 1001`

* `0011`是固定的，可以使用右移来判断是否结果为3
  * `x>>4`
* `0000 - 1001`，最大为`1001`，可以将其减去 `0xa` 来判断是否为负数，若为负数则符合
  * `x & 0xf`获得最后四位
  * `~0xa + 1 `得到`-0xa`
  * 相加，通过负权为是否为1判断是否为负数

```C
int isAsciiDigit(int x) {
  int a = !((x>>4) ^ 3); //is 0011?
  int b = (x& 0xf) + (~0xa + 1); //range from 0000 to 1001?
  int c = b>>3;   //b is negative?
  return a & !!c;
}
```



7.`int conditional(int x, int y, int z)`

要求：

```
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
```

我的分析：

* `!!x`判断x是否为零
* 然后将其复制为32位，然后与y进行按位与运算
* 对其按位取反，然后与z按位与运算

代码如下：正好16个运算符

```C
int conditional(int x, int y, int z) {
  int t = !!x;
  t = (t<<1) + t;
  t = (t<<2) + t;
  t = (t<<4) + t;
  t = (t<<8) + t;
  t = (t<<16) + t;
  return (t&y) | (~t&z);
}
```

关键在于在`!!x`为1时，变为`0xffff`，为0时变为`0x0000`

不像前面那样按位复制的方法，因为`0xffff`其实就是 1 的相反数，直接`~x + 1`即可，而0的相反数为0

`x = ~x+1`替代前面变换，得

```C
int conditional(int x, int y, int z) {
  int t = !!x;
  t = (~t) + 1;
  return (t&y) | (~t&z);
}
```



8.`int isLessOrEqual(int x, int y) ` **

要求:

```
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
```

**分析：**

> 若y>=x则返回1。将y-x（y+~x+1），当y、x同号时判断y-x符号位即可，当y、x异号时可能会发生溢出，需要看y、x的符号位。

找到一种只需要判断某个式子，使得只要判断其为负数或正数，就可以得到小于等于的结果

* 可以用 y - x，
  * 若结果为负，返回 0
    * 但当y为-，x为+时，会溢出
  * 其他结果，则返回 1
    * 当y为+，x为-时，会溢出

**结果：**

未通过`(-2147483648[0x80000000],2147483647[0x7fffffff])`

分析得，当负数减正数，正数减负数时，会有溢出的可能，但此时答案返回值是固定的。

* 可以分三种情况：
* 1. x为-，y为+时，直接返回1
  2. x为+，y为-时，直接返回0
  3. 其他正常情况，直接返回y-x的符号位

```C
int isLessOrEqual(int x, int y) {
    
  int c_x = x>>31;
  int c_y = y>>31;
  int ans = (~x +1) +y;
  int c_ans = ans>>31;
  int c1 = c_x& (!c_y); //c_x -, c_y +
  int c2 = c_y& (!c_x); //c_x +, c_y -

  return c1 | (!c2 & !c_ans);
}
```

只考虑返回 1 的情况：

1. x为-，y为+
2. y-x为正或零



9.`int logicalNeg(int x)`

要求：

```
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
```

分析：

`x==0 ? 1:0`

* 对于非零数，发现 `x|(~x+1)` 负权位必为1
* 而该操作对于 0 无影响
* 可以利用该特性，`(x|(~x+1))>>1` 由于1为最高位，得到的必为`-1`

得到：

```C
int logicalNeg(int x) {
  return ((x|(~x+1))>>31) + 1;
}
```



10.`int howManyBits(int x)`

要求：

```
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
```

分析：

1. 如果是一个正数，则需要找到它最高的一位（假设是n）是1的，再加上符号位，结果为n+1；

2. 如果是一个负数，则需要知道其最高的一位是0的（例如4位的1101和三位的101补码表示的是一个值：-3，最少需要3位来表示），可以对其求相反数。
3. 然后
   1. 从高16位开始判断是否含有1，若有则至少不需要判断低16位，至少有16位来表示，去除低16位，
   2. 对高十六位的高八位判断是否含有1，若有。。。。
   3. 判断完后需要加一位符号位

代码：

```C
int howManyBits(int x) {
  int b16,b8,b4,b2,b1,b0;
  int sign = (x>>31);
  x = (~sign & x) | (sign & ~x);
    
  b16 = (!!(x>>16)) <<4;
  x = x>>b16;
  b8 = (!!(x>>8)) <<3;
  x = x>>b8;
  b4 = (!!(x>>4)) <<2;
  x = x>>b4;
  b2 = (!!(x>>2)) <<1;
  x = x>>b2;
  b1 = (!!(x>>1)) <<0;
  x = x>>b1;
  b0 = x;

  return b16+b8+b4+b2+b1+b0+1;
}
```



## 3  *FLOATING POINT CODING*

1.`unsigned floatScale2(unsigned uf)`

要求：

```
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
```

分析：

1. 先使用如下技巧，将标志位、阶码和尾数分离开来

可以使用使用如下技巧取二进制表示的某几位，取uf第四位开始的四位二进制

```
uf>>(3)&(1111)
```

2. 然后逻辑：
   1. 如果`e==0`，非规格浮点数
      1. 若`m!=0`，只需将 m 乘二
      2. 否则，该浮点数表示零，不需要改动
   2. 如果`e==0xff`，表示特殊值(`NaN`、`INF`)
   3. 否则，此时为规格化浮点数，只需将阶码加一

```C
unsigned floatScale2(unsigned uf) {
  unsigned um = uf&(0x7fffff);
  unsigned ue = (uf>>23)&(0xff);
  unsigned us = (uf>>31)&(0x1);
  if(ue == 0 ){
    if(um != 0){
      um *=2;
    }
  }else if( ue == 0xff){

  }else{
    ue = ue+1;
  }
  unsigned ans=(us<<31) | (ue<<23) | (um);
  return ans;
}
```

2.`int floatFloat2Int(unsigned uf)`

要求：

```
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x8000 0000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
```

分析：

先分离出标志位s、阶码e和尾数m

1.对于规格化浮点数：

* 尾数23位前补1
* 指数可由阶码得： $l=e-(2^{k-1}-1)$ ，k为8
  * 若$l <0 $，说明表示纯小数，返回0即可
  * 若$0\le l \le 23$，说明有舍入，将尾数右移`24-l-1`
  * 若$23<l\le 31$，说明无舍入，可以完整表示，将尾数左移`l-23`
  * 若$l>31$，说明太大了无法表示，返回`Tmin`

2.对于非规格化浮点数：`e`为`0x 00`

* 直接返回`0x0`

3.对于特殊值：e为`0xff`

* 直接返回`0x8000 0000`

代码如下：

```C
int floatFloat2Int(unsigned uf) {
    unsigned s = (uf>>31)&(0x1);
    unsigned e = (uf>>23)&(0xff);
    unsigned m = (uf)&(0x7fffff);
    unsigned ans=0;
    int l;
    //printf("%08x %08x %08x\n",s,e,m);


    if(e == 0){
        ans = 0;
    }else if(e == 0xff){
        ans = 0x80000000;
    }else{
        m = m | (0x800000);
        l = e-(127);

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
    // printf("0x%08x %d\n",ans,ans);
  return ans;
}
```



3.`unsigned floatPower2(int x)`

要求：

```
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
```

分析：

`denorm`: 非规格化浮点数

因为给定的x即为`E=e-Bias`的值，而根据e的不同值：因为单精度浮点数所能表示的指数E范围为`-126~127`

1.如果$E>2^7-1=127$ ，则`too large`

2.如果$E<-2^7+2=-126$, 则`denorm`

3.如果$-2^7+2\le E \le 2^7-1$, 则可以正常表示

1. 取x的低八位作为e的位表示
2. 标志位为0
3. m为0

代码如下

```C
unsigned floatPower2(int x) {
  unsigned s = 0;
  unsigned m = 0;
  unsigned e = x&(0xff);
  unsigned ans;
  if(x>127){
    ans = 0x7f800000;
  }else if(x<-126){
    ans = 0x0;
  }else{
    ans = (e+127)<<23;
  }
  return ans;
}
```

## 总结

![image-20210928131504228](E:\2nd_summer_holiday\CSAPP\CSAPP_Labs.assets\image-20210928131504228.png)

* `INT Coding`部分，由于~~限制了太多操作~~(自己太菜了)，部分`function`在思考后实在做不出来，就参考了网上已完成的实验代码，也已理解
* `FLOAT Coding`部分完全是自己琢磨完成的，十分有成就感！对单精度浮点数有了更深入的理解

#  2 Boomb

* 读完第三章内容
* 除了浮点数部分

## 2.1 阅读  bomblab

> This is an x86-64 bomb for self-study students. 
>
>  The Bomb Lab teaches students principles of machine-level programs, as well as general debugger and reverse engineering skills



> To avoid accidentally detonating the bomb, you will need to learn how to single-step through the assembly
> code and how to set breakpoints. You will also need to learn how to inspect both the registers and the
> memory states. One of the nice side-effects of doing the lab is that you will get very good at using a
> debugger. This is a crucial skill that will pay big dividends the rest of your career.

**Hints：**

* gdb: 
  * 对源码或者汇编代码单步执行，以免炸弹爆炸
* objdump -t
  * 输出炸弹的符号表
  * the names of all functions and global variables in the bomb, the names of all the functions the bomb calls, and their addresses.
* objdump -d
  * 反汇编二进制文件
* strings
  * 

##  2.2 准备工作

**反汇编bomb二进制文件**

`objdump -d bomb >> bomb.s`



**输出bomb的符号表**

`objdump -t bomb >> bomb_symbol_table`



**读main函数**

* initialize_bomb(): 启动炸弹

* > Six phases must be more secure than one phase!

  * 有六个阶段需要完成

* **phase_1**(input);

* **phase_2**(input);

* **phase_3**(input);

* **phase_4**(input);

* **phase_5**(input);

* **phase_6**(input);

  * 可能需要gbd单步调试每个阶段，

## 2.3 phase 1

找到phase1对应的汇编代码：

```assembly
0000000000400ee0 <phase_1>:
  400ee0:	48 83 ec 08          	sub    $0x8,%rsp
  400ee4:	be 00 24 40 00       	mov    $0x402400,%esi
  400ee9:	e8 4a 04 00 00       	callq  401338 <strings_not_equal>	#调用函数，0x402400(%esi),我们输入的字符串(%rdi)
  400eee:	85 c0                	test   %eax,%eax	
  400ef0:	74 05                	je     400ef7 <phase_1+0x17>		#如果返回值%eax为零，则拆弹成功
  400ef2:	e8 43 05 00 00       	callq  40143a <explode_bomb>
  400ef7:	48 83 c4 08          	add    $0x8,%rsp
  400efb:	c3                   	retq  
```



phase1调用的函数strings_not_equal:

```assembly
0000000000401338 <strings_not_equal>:
  401338:	41 54                	push   %r12
  40133a:	55                   	push   %rbp
  40133b:	53                   	push   %rbx
  40133c:	48 89 fb             	mov    %rdi,%rbx
  40133f:	48 89 f5             	mov    %rsi,%rbp
  401342:	e8 d4 ff ff ff       	callq  40131b <string_length>
  401347:	41 89 c4             	mov    %eax,%r12d
  40134a:	48 89 ef             	mov    %rbp,%rdi
  40134d:	e8 c9 ff ff ff       	callq  40131b <string_length>
  401352:	ba 01 00 00 00       	mov    $0x1,%edx
  401357:	41 39 c4             	cmp    %eax,%r12d
  40135a:	75 3f                	jne    40139b <strings_not_equal+0x63>
  40135c:	0f b6 03             	movzbl (%rbx),%eax		#将我们输入的字符串，复制到%eax中
  40135f:	84 c0                	test   %al,%al
  401361:	74 25                	je     401388 <strings_not_equal+0x50>
  401363:	3a 45 00             	cmp    0x0(%rbp),%al	#重点，因为%rbp存着0x402400，而%rax存着我们输入的字符串
  401366:	74 0a                	je     401372 <strings_not_equal+0x3a>
  401368:	eb 25                	jmp    40138f <strings_not_equal+0x57>
  40136a:	3a 45 00             	cmp    0x0(%rbp),%al
  40136d:	0f 1f 00             	nopl   (%rax)
  401370:	75 24                	jne    401396 <strings_not_equal+0x5e>
  401372:	48 83 c3 01          	add    $0x1,%rbx
  401376:	48 83 c5 01          	add    $0x1,%rbp
  40137a:	0f b6 03             	movzbl (%rbx),%eax
  40137d:	84 c0                	test   %al,%al
  40137f:	75 e9                	jne    40136a <strings_not_equal+0x32>
  401381:	ba 00 00 00 00       	mov    $0x0,%edx
  401386:	eb 13                	jmp    40139b <strings_not_equal+0x63>
  401388:	ba 00 00 00 00       	mov    $0x0,%edx
  40138d:	eb 0c                	jmp    40139b <strings_not_equal+0x63>
  40138f:	ba 01 00 00 00       	mov    $0x1,%edx
  401394:	eb 05                	jmp    40139b <strings_not_equal+0x63>
  401396:	ba 01 00 00 00       	mov    $0x1,%edx
  40139b:	89 d0                	mov    %edx,%eax
  40139d:	5b                   	pop    %rbx
  40139e:	5d                   	pop    %rbp
  40139f:	41 5c                	pop    %r12
  4013a1:	c3                   	retq   
```


调用的explode_bomb：

```assembly
000000000040143a <explode_bomb>:
  40143a:	48 83 ec 08          	sub    $0x8,%rsp
  40143e:	bf a3 25 40 00       	mov    $0x4025a3,%edi
  401443:	e8 c8 f6 ff ff       	callq  400b10 <puts@plt>
  401448:	bf ac 25 40 00       	mov    $0x4025ac,%edi
  40144d:	e8 be f6 ff ff       	callq  400b10 <puts@plt>
  401452:	bf 08 00 00 00       	mov    $0x8,%edi
  401457:	e8 c4 f7 ff ff       	callq  400c20 <exit@plt>
```



分析得：函数strings_not_equal,查看了我们输入的字符串和内存地址0x402400处所存的是否相等。

* 取出内存地址的值：使用`examine`缩写`x`命令，查看值 [参考](https://blog.csdn.net/zzymusic/article/details/4815142)
  * `x/s 0x402400`
  * 得到：`0x402400:       "Border relations with Canada have never been better."`

