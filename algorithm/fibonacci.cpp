#include <iostream>
using namespace std;

int fibonacci(int);

int main()
{
    int n;
    cout << "Input an non-negative integer, to get its fibonacci: ";
    cin >> n;
    cout << "\nYour input is " << n << ", its fibonacci is " << fibonacci(n) << endl;
    return 0;
}

int fibonacci(int n)
{
    if(n == 1 || n == 0)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}
