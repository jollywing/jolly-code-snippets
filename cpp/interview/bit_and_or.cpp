
#include <iostream>
using namespace std;

int main()
{
    int x = 2, y, z;
    x *= (y = z = 5);
    cout << x << endl;    // x should be 10

    z = 3;
    x == (y = z);
    cout << x << endl;          // x should still be 10

    x = (y == z);
    cout << x << endl;          // x == 1?

    x = (y&z); cout << x << endl; // x == 3?

    x = (y && z); cout << x << endl; // x == 1?

    y = 4;
    x = (y | z); cout << x << endl; // x == 7?

    x = (y || z); cout << x << endl; // x == 1?
    return 0;
}

// Yeap! all are right!
