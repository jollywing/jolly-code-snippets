#include <iostream>
using std::cout; using std::endl;

class Timer {
private:
    int interval;
public:
    
    Timer(int v){
        interval = v;
    }

    int GetInterval() {
        return interval;
    }
};

class Clock {
private:
    int price;
public:
    // forbid implicit calling constructor
    explicit Clock(int p) {
        price = p;
    }
};

// void PrintTimer(Timer &t) won't work.
void PrintTimer(Timer t)
{
    cout << t.GetInterval() << endl;
}

void TestImplicitConvert()
{
    // It's equal: Timer t1 = Timer(2);
    Timer t1 = 2;

    // It's equal: Timer t2 = Timer('a');
    // 'a' has a int value.
    Timer t2 = 'a';

    // It's equal: PrintTimer(Timer('b'));
    PrintTimer('b');
}

void TestExplicitConstructor()
{
    Clock c1 = Clock(12);

    // Error: won't call constructing implicitly
    Clock c2 = 98;
}

int main()
{
    TestImplicitConvert();
    TestExplicitConstructor();
    return 0;
}
