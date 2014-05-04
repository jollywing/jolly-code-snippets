#include <iostream>

// You can use std::exception directly, but if you want to use overflow_error, you should
#include <stdexcept>

using std::cout;
using std::endl;
using std::overflow_error;

double divide(double, double);

void TestOverflowException()
{
    try {
        // divided by 0 won't throw exception automatically.
        // double r = 3 / 0;
        double r = divide(3, 0);
        cout << r << endl;
    }
    catch(overflow_error & e){
        cout << e.what() << endl;
    }
}

double divide(double d, double divider)
{
    if(divider == 0){
        throw overflow_error("divided by zero!");
    }
    return d / divider;
}

int main()
{
    TestOverflowException();
    cout << "hello, world!" << endl;
    return 0;
}
