//
//  RotateVetor.cpp
//  FirstPart
//
//  Created by ZhangXiaoMBS on 2017/6/23.
//  Copyright © 2017年 ZhangXiaoMBS. All rights reserved.
//

#include "RotateVetor.hpp"

int gcd(int a, int b);
void printA(int a[], int size);

/******************************************************************************
 *函数名称：rotateVetor(int rotdist, int size)
 *函数功能：旋转向量
 *入口参数：rotdist：偏移量， size：向量大小
 *返 回 值：无
 *******************************************************************************/
void rotateVetor(int rotdist, int size) {
    int a[size];
    
    for (int i = 0; i < size; i++) {
        a[i] = i + 1;
    }
    
    /// 开始旋转
    int i, j, t, k = 0;
    for (i = 0; i < gcd(rotdist, size); i ++) {
        t = a[i];
        j = i;
        
        do {
            k = j + rotdist;
            if (k >= size) {
                k -= size;
            }
            
            if (k == i) {
                break;
            }
            
            a[j] = a[k];
            j = k;
            
            printA(a, size);
        } while (k != i);
        
        a[j] = t;
        
        printf("************************\n");
        printA(a, size);
        printf("************************\n");
    }
}

/******************************************************************************
 *函数名称：gcd(int a, int b)
 *函数功能：求取两个数的最大公约数
 *入口参数：
 *返 回 值：int 最大公约数
 *算法思路：辗转相除法，两者一直相除，如果为0，则除数即为最大公约数，不为0，则取余，继续相除
 *******************************************************************************/
int gcd(int a, int b) {
    int temp = b;
    
    if (0 == b) {
        return a;
    }
    
    while (a % b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    
    return temp;
}

/******************************************************************************
 *函数名称：gcd2(int a, int b)
 *函数功能：求取两个数的最大公约数
 *入口参数：
 *返 回 值：int 最大公约数
 *算法思路：辗转相减法，两者一直相减（max -= min），直到两者相等
 *******************************************************************************/
int gcd2(int a, int b) {
    int max = a > b ? a : b;
    int min = a - b ? a : b;
    
    while (max != min) {
        max -= min;
    }
    
    return min;
}

void printA(int a[], int size) {
    for (int i = 0; i < size; i ++) {
        printf("%d  ", a[i]);
    }
    
    printf("\n");
}

/******************************************************************************
 *函数名称：gcd3(int a, int b)
 *函数功能：求取两个数的最大公约数
 *入口参数：
 *返 回 值：int 最大公约数
 *算法思路：扩展欧几里得算法，实质是使用的辗转相除法
 基本算法：对于不完全为 0 的非负整数 a，b，gcd（a，b）表示 a，b 的最大公约数，必然存在整数对 x，y ，使得 gcd（a，b）=ax+by。
 
 证明：设 a>b。
 
 　　1，显然当 b=0，gcd（a，b）=a。此时 x=1，y=0；
 
 　　2，ab!=0 时
 
 　　设 ax1+by1=gcd(a,b);
 
 　　bx2+(a mod b)y2=gcd(b,a mod b);
 
 　　根据朴素的欧几里德原理有 gcd(a,b)=gcd(b,a mod b);
 
 　　则:ax1+by1=bx2+(a mod b)y2;
 
 　　即:ax1+by1=bx2+(a-(a/b)*b)y2=ay2+bx2-(a/b)*by2;
 
 　　根据恒等定理得：x1=y2; y1=x2-(a/b)*y2;
 
 这样我们就得到了求解 x1,y1 的方法：x1，y1 的值基于 x2，y2.
 
 　  上面的思想是以递归定义的，因为 gcd 不断的递归求解一定会有个时候 b=0，所以递归可以结束。
 *******************************************************************************/
int gcd3(int a, int b, int x, int y) {
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }
    int r = gcd3(b, a%b, x, y);
    int t = x;
    x = y;
    y = t - a/b * y;
     return r;
}
