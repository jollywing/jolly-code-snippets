#include <iostream>
#include <assert.h>

using namespace std;

// 这其实是一个查找正整数的二进制形式含有多少个1的算法。
// x = x & (x -1);
int get_one_bit_count(int x) {
    int count = 0;
    while(x){
        count ++;
        x = x & (x - 1);
    }
    return count;
}

int main() {
    assert(get_one_bit_count(32) == 1);
    assert(get_one_bit_count(15) == 4);
    assert(get_one_bit_count(7) == 3);
    assert(get_one_bit_count(0) == 0);
    assert(get_one_bit_count(-2) == 31);
    return 0;
}

// 9999的二进制为10011100001111
