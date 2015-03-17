#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    float a = 1.0f;
    cout << (int)a << endl; // 1
    cout << &a << endl;     // 0xbfd5161c, vary each time
    // 把浮点数的前4个字节作为整数显示，相当于 *((int *)&a)
    cout << (int &)a << endl;   // 1065353216,
    cout << *((int *)&a) << endl;
    cout << boolalpha << ((int)a == (int &)a) << endl; // false

    float b = 0.0f;
    cout << (int)b << endl;     // 0
    cout << &b << endl;
    cout << (int &)b << endl;
    cout << boolalpha << ((int)b == (int &)b) << endl;

    return 0;
}
