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


#include <iostream>
#include <bitset>
#include <vector>

#include <cstdio>
#include <cstdlib>      // srand, rand
#include <ctime>        // time, clock_t
#include <cassert>      // assert
#include <math.h>

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
static void swap(int *a, int *b)
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
        swap(&a[i], &a[i+rand()%(n-i)]);
    }
}

void searchLostNum(int a[], int n) {
    /// 整形有32位，所以最多循环32次，判断丢失的整数具体位置
    for (int i = 0; i < 32; i++) {
        
        int oneNum, zeroNum = 0;
    }
}

/************************************************************************/
// 函数名称：getbit
// 函数返回：0或1
// 函数目的：找出value的pos比特位的值
// 使用条件：value范围是[0, 2^32-1]
/************************************************************************/
bool getbit(int32_t value, int32_t pos)
{
    assert(pos >= 0 && pos < 32);
    
    int32_t mask = 1;    // 表示二进制掩码
    int32_t value_32 = value;
    
    return ((value_32 >> pos & mask) == mask);
}

/************************************************************************/
// 函数名称：find_missing_integers
// 函数返回：无
// 函数目的：找出小于max_counts(不包括)的所有缺失的整数
// 使用条件：vecints里面的数不重复, pos=0时，vetints里面最大值小于max_counts
/************************************************************************/
bitset<32> bit_missing_integer;
void find_missing_integers(const vector<int32_t>& vecints, const int32_t max_counts, int32_t pos=0)
{
    // 计算相应bit位的0，1计数
    int32_t counts_0 = 0, counts_1 = 0;
    counts_0 = ceil(1.0 * max_counts / 2 );    // ceil向上取整
    counts_1 = max_counts - counts_0;
    
    vector<int32_t> vecints_0, vecints_1;
    for (size_t i = 0; i != vecints.size(); ++i) {
        if (!getbit(vecints[i], pos)) { vecints_0.push_back(vecints[i]); }
        else { vecints_1.push_back(vecints[i]); }
    }
    
    // 第pos位缺1的情况
    if (counts_1 - vecints_1.size() > 0){
        bit_missing_integer[pos] = 1;
        find_missing_integers(vecints_1, counts_1, pos + 1);
    }
    
    // 第pos位缺0的情况
    if (counts_0 - vecints_0.size() > 0){
        bit_missing_integer[pos] = 0;
        
        if (counts_0 == 1 && counts_1 == 0){ // 临界位
            printf("%ld\t", bit_missing_integer.to_ulong());
            return;
        }
        else {  // 递归调用
            find_missing_integers(vecints_0, counts_0, pos + 1);
        }
    }
    
    return;
}

void print_missing_integers()
{
    int myints[9] = {1, 19, 4, 6, 18};
    std::vector<int> myvecints(myints, myints + sizeof(myints) / sizeof(int) );
    
    find_missing_integers(myvecints, 20);
    return;
}
