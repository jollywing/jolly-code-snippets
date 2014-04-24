
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // ERROR: a reference variable must be initialized
    // when it is declared.
    // int &r1;

    // ERROR: r1 is a non const reference, so it can not refer to a const.
    // int &r1 = 5;

    // RIGHT! but it is unnecessary.
    // const int &r1 = 5;

    string a = "Hello";
    string b = "It's a sunny day!";

    string &r1 = a;
    cout << r1 << endl;
    a.append(" world!");
    cout << r1 << endl;
    a = "Null";
    cout << r1 << endl;

    // 引用可以被重新赋值？对g++来说是可以的。
    r1 = b;
    cout << r1 << endl;
    a.erase();
    cout << r1 << endl;

    // This will result in runtime segment fault because NULL can not be referenced.
    // b.assign(NULL);
    // cout << r1 << endl;

    // 引用变量是可以指向空值的，但引用变量变量要是const int | const char | const short ...
    // 赋值时会把空值转换成整型，有警告错误。
    const int &r2 = NULL;

    // 编译时不报错，但运行时会报错。以NULL为参数的字符串构造符不合法
    const string &r3 = NULL;
    cout << r3 << endl;

    return 0;
}
