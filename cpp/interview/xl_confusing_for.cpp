// 迅雷2007年题目
#include <iostream>

using namespace std;

int main() {
    int a, x;
    for(a = 0, x = 0; a <= 1 && !x++; a++){
        a++;
    }
    cout << a << x << endl;     // 21

    for(a = 0, x = 0; a <= 1 && !x++;) {
        a++;
    }
    cout << a << x << endl;     // 12
    return 0;
}
