//
//  main.cpp
//  FirstPart
//
//  Created by ZhangXiaoMBS on 2017/6/20.
//  Copyright © 2017年 ZhangXiaoMBS. All rights reserved.
//

#include <iostream>
#include <set>
#include <bitset>

#include <time.h>

//#include "BitSort.hpp"

#include "RotateVetor.hpp"

#include "SearchLostNum.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    
    /// 直接使用C++的set容器进行排序
    //sortBySet();
    
    /// 直接使用C++的bitset进行位图构造并排序
    //sortByBitSet();
    
    /// 使用位图压缩，构造整形数组存储位图信息并排序
    //sortByBit();
    
    //rotateVetor(5, 12);
    
    print_missing_integers();
    
    return 0;
}
