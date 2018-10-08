#include <iostream>
#include <stdlib.h>

using namespace std;

int get_biggest_common_divisor(int n1, int n2)
{
    int bigger = (n1 + n2 + abs(n1 - n2)) / 2;
    int smaller = (n1 + n2 - abs(n1 - n2)) / 2;
    // cout << "bigger: " << bigger << endl;
    // cout << "smaller: " << smaller << endl;
    int r = bigger % smaller;
    while(r != 0) {
        bigger = smaller;
        smaller = r;
        r = bigger % smaller;
    }
    return smaller;
}

int get_least_common_mutiple(int n1, int n2)
{
    return n1 * n2 / get_biggest_common_divisor(n1, n2);
}

int main()
{
    int n1, n2;
    cout << "Input 2 integers, seperate them by new line:" << endl;
    cin >> n1 >> n2;
    cout << n1 << "," <<  n2 << endl;
    cout << "their the biggest common divisor is " <<
            get_biggest_common_divisor(n1, n2) << endl;
    cout << "Their the least common mutiple is " <<
            get_least_common_mutiple(n1, n2) << endl;
    return 0;
}
