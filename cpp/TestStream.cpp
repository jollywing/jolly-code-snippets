
#include <iostream>
#include <ios>                  // define streamsize
#include <iomanip>              // define setw
#include <assert.h>
using std::cout;
using std::endl;
using std::streamsize; using std::setprecision;
using std::setw; using std::setfill;

void TestCoutWidth()
{
    cout << "---------- TEST WIDTH ----------" << endl;
    streamsize w = cout.width();
    cout << "the original width: " << w << endl;
    cout << setw(5);
    w = cout.width();
    // only 'a' is left padded with space, then width reset to 0.
    cout << 'a' << 'b' << endl;
    streamsize w2;
    w2 = cout.width();
    cout << "width reset to " << w2 << endl;

    w = cout.width(5);
    cout << w << w << endl;
    assert(w == 0);
    cout << "width reset to 0 after cout a field." << endl;

    w = cout.width(3);
    cout << "HH";
    w = cout.width();
    cout << "stream width reset to " << w << endl;
    cout << endl;
}

void TestCoutFill()
{
    cout << "---------- TEST FILL ----------" << endl;
    char c = cout.fill();
    cout << "The original cout filled with " << c << endl;
    cout << setfill('_') << setw(10) << 'a' << endl;
    cout << setw(10) << 'a' << endl;
    cout << "The fill char keep unchanaged." << endl;
    c = cout.fill();
    cout << "cout filled with " << c << endl;
    cout << endl;
}

void TestCoutAlign()
{
    cout << "---------- TEST ALIGN ----------" << endl;
    // left align
    cout << setw(10) << std::left << 'c' << endl;
    cout << setw(10) << 'c' << endl;
    cout << "Alignment keep unchanged." << endl;
    cout << endl;
}

void TestPrecision()
{
    cout << "---------- TEST PRECISION ----------" << endl;
    streamsize prec = cout.precision();
    cout << "The original precision is " << prec << endl;
    cout << setprecision(3) << 12.23 << '\t' << 12.23 << endl;

    // only get the current precision
    prec = cout.precision();
    assert(prec == 3);
    prec = cout.precision();
    assert(prec == 3);

    // keep the float point bits fixed
    cout << std::fixed << 0.1 << '\t' << 1234.0 << '\t' << 1.2 << endl;

    cout << endl;
}

int main()
{
    TestCoutWidth();
    TestCoutFill();
    TestCoutAlign();
    TestPrecision();
    return 0;
}
