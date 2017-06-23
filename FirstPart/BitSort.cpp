//
//  BitSort.cpp
//  FirstPart
//
//  Created by ZhangXiaoMBS on 2017/6/23.
//  Copyright © 2017年 ZhangXiaoMBS. All rights reserved.
//

#include "BitSort.hpp"

using namespace std;

// int 类型有4个字节，即32位
#define BITSPERWORD 32

// 定义右移的位数（即除以32，表示右移5位）
#define SHIFT 5

// 16进制31 二进制的话就是 0001 1111
#define MASK 0x1F

// 最大整数
#define N 10000000

// 最大数量
#define K 1000000

// 存放输入数据
int a[N];

// 位图排序使用的数组
int sortBit[1 + N/BITSPERWORD];

/******************************************************************************
 *函数名称：swap(int *a, int *b)
 *函数功能：交换数组内两个元素的位置
 *入口参数：
 *返 回 值：无
 *******************************************************************************/
void swap(int *a, int *b)
{
    if(*a != *b){                 // 异或操作 交换两个数字的位置
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
    
}

#pragma mark - 产生随机数
/******************************************************************************
 *函数名称：void generateDiffRandV1(int a[], int n)
 *函数功能：产生互不相同的随机数
 *入口参数：
 *返 回 值：无
 *备 注：以空间换时间
 *******************************************************************************/
void generateDiffRandV1(int a[], int n, int k)
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

/******************************************************************************
 *函数名称：void generateDiffRandV2(int a[], int n)
 *函数功能：产生互不相同的随机数(产生随机数的范围是1~n-1)
 *入口参数：
 *返 回 值：无
 *
 *思 路：先生成一个放置座号的数组，然后从中随机抽取，抽取后为防止重复，立即归零。
 * ：每次生成座号，只需判断是否为0 即可，大大提高了程序执行的效率。
 *******************************************************************************/
void generateDiffRandV2(int a[], int n)
{
    int *flag =(int *)malloc(sizeof(int) * n);
    static int flag_once = 0;
    int i, index;
    
    for(i = 0; i < n; i++)
        flag[i] = i+1;
    if(!flag_once){
        srand((unsigned)time(0));
        flag_once = 1;
    }
    
    for(i = 0; i < n;){
        index = rand() % n;
        if(flag[index] != 0){
            a[i++] = flag[index]-1;
            flag[index] = 0;
        }
    }
    free(flag);
}

/******************************************************************************
 *函数名称：void printArray(int a[], int n)
 *函数功能：打印数组
 *入口参数：
 *返 回 值：无
 *
 *思 路：先生成一个放置座号的数组，然后从中随机抽取，抽取后为防止重复，立即归零。
 * ：每次生成座号，只需判断是否为0 即可，大大提高了程序执行的效率。
 *******************************************************************************/
void printArray(int a[], int n)
{
    int i;
    
    for (i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

#pragma mark - 位图排序
/******************************************************************************
 *函数名称：void generateDiffRandV2(int a[], int n)
 *函数功能：产生互不相同的随机数(产生随机数的范围是1~n-1)
 *入口参数：
 *返 回 值：无
 *
 *思 路：先生成一个放置座号的数组，然后从中随机抽取，抽取后为防止重复，立即归零。
 * ：每次生成座号，只需判断是否为0 即可，大大提高了程序执行的效率。
 *******************************************************************************/
void sortBySet() {
    generateDiffRandV1(a, N, K);
    printf("Got the num  -- %ld\n", time(0));
    
    long beginTime = time(0);
    printf("Sort Begin  -- %ld\n", beginTime);
    
    set<int> S;
    
    for (int temp = 0; temp < K; temp++) {
        S.insert(a[temp]);
    }
    
    int i = 0;
    set<int>::iterator j;
    for (j = S.begin(); j != S.end(); ++j) {
        //cout << *j << "  ";
        a[i] = *j;
        i++;
    }
    
    cout << endl;
    long endTime = time(0);
    printf("Sort End    -- %ld\n", endTime);
    printf("************************The Sort Time %ld\n", endTime - beginTime);
}

void setBit(int i) {
    /// i & MASK 相当于 除以32然后取余
    sortBit[i>>SHIFT] |= (1<<(i & MASK));
}

void clrBit(int i) {
    /// i & MASK 相当于 除以32然后取余
    sortBit[i>>SHIFT] &= ~(1<<(i & MASK));
}

int testBit(int i) {
    /// i & MASK 相当于 除以32然后取余
    return sortBit[i>>SHIFT] & (1<<(i & MASK));
}

/******************************************************************************
 *函数名称：void sortByBit()
 *函数功能：利用位图进行排序
 *入口参数：
 *返 回 值：无
 *
 *思 路：生成一个整形数组，每一个数组都可以表示32个整数是否存在，存在则找出对应的位，将其置为1
 * ：每次从数组中取出一个整数a[i], 然后判断这个数在sortBit里面的位置
 *******************************************************************************/
void sortByBit() {
    generateDiffRandV1(a, N, K);
    printf("Got the num  -- %ld\n", time(0));
    
    long beginTime = time(0);
    printf("Sort Begin  -- %ld\n", beginTime);
    
    for (int i = 0; i < K; i++) {
        clrBit(a[i]);
    }
    
    int i = 0;
    while (i < K) {
        setBit(a[i]);
        i++;
    }
    
    for (int i = 0; i < K; i++) {
        if (testBit(i)) {
            cout << i << "  ";
        }
    }
    
    cout << endl;
    long endTime = time(0);
    printf("Sort End    -- %ld\n", endTime);
    printf("************************The Sort Time %ld\n", endTime - beginTime);
    cout << endl;
}

/******************************************************************************
 *函数名称：void generateDiffRandV2(int a[], int n)
 *函数功能：产生互不相同的随机数(产生随机数的范围是1~n-1)
 *入口参数：
 *返 回 值：无
 *
 *思 路：先生成一个放置座号的数组，然后从中随机抽取，抽取后为防止重复，立即归零。
 * ：每次生成座号，只需判断是否为0 即可，大大提高了程序执行的效率。
 *******************************************************************************/
void sortByBitSet() {
    generateDiffRandV1(a, N, K);
    printf("Got the num  -- %ld\n", time(0));
    
    long beginTime = time(0);
    printf("Sort Begin  -- %ld\n", beginTime);
    
    int n = 0;
    
    // 位数可以多1位，避免数据丢失
    bitset<1 + N> bit;                     //初始默认所有二进制位为0
    
    while(n < K)
    {
        bit.set(a[n], 1);                   //将第n位置1
        n ++;
    }
    
    for(int i = 0; i <= K + 1; i++)
    {
        if(bit[i] == 1)
            cout << i << "  ";
    }
    
    cout << endl;
    long endTime = time(0);
    printf("Sort End    -- %ld\n", endTime);
    printf("************************The Sort Time %ld\n", endTime - beginTime);
    cout << endl;
}
