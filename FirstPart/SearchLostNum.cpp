//
//  SearchLostNum.cpp
//  FirstPart
//
//  Created by ZhangXiaoMBS on 2017/6/23.
//  Copyright © 2017年 ZhangXiaoMBS. All rights reserved.
//

#include "SearchLostNum.hpp"

#include <iostream>

using namespace std;

//// 最大整数
//#define N 10000000
//
//// 最大数量
//#define K 1000000

/******************************************************************************
 *函数名称：swap(int *a, int *b)
 *函数功能：交换数组内两个元素的位置
 *入口参数：
 *返 回 值：无
 *******************************************************************************/
void swap1(int *a, int *b)
{
    if(*a != *b){                 // 异或操作 交换两个数字的位置
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
    
}

/******************************************************************************
 *函数名称：void generateDiffRandV(int a[], int n, int k)
 *函数功能：产生随机缺失部分数据的数组
 *入口参数：
 *返 回 值：无
 *
 *思 路：随机生成一个整形数组，并且每个整数只出现一次，且整数的最大值大于数组个数
 * ：因为随机数的最大值大于数组长度，则产生的数组至少缺失一个
 * ：当然从逻辑上来讲，还是有可能出现数组刚好完全包含所有元素，但如果数组足够大，那么这个概率几乎可以忽略不计
 *******************************************************************************/
void generateDiffRandV(int a[], int n, int k)
{
    int i;
    time_t t;
    
    for (i = 0; i < n; i++){
        a[i] = i;
    }
    
    srand((int)time(&t));
    for (i = 0; i < k; i++){
        swap1(&a[i], &a[i+rand()%(n-i)]);
    }
}
