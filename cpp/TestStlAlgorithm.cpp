#include <vector>
#include <assert.h>
#include <iostream>
#include <numeric>              // define accumulate

using std::cout; using std::endl;
using std::accumulate;

void TestArraySize()
{
    int a[5] = {10, 20, 30, 40, 50};
    int s = sizeof(a) / sizeof(int);
    assert(s == 5);

    char v[] = "Hello";
    int l = sizeof(v) /sizeof(char);
    assert(l == 6);

    for(int i = 0; i < l; i++) {
        int t = v[i];
        cout << t << '\t';
    }
    cout << endl;
}

void TestAccumulate()
{
    int a[] = {20, 40, 60, 80};
    int size_a = sizeof(a) / sizeof(int);
    std::vector<int> v(a, a + size_a);
    assert(v.size() == 4);

    int i = 0;
    i = accumulate(v.begin(), v.end(), i);
    assert(i == 200);

    std::string s1 = "Sun";
    std::string s2 = "Shine";
    std::string s = accumulate(s2.begin(), s2.end(), s1);
    assert(s == "SunShine");
}

int main()
{
    TestArraySize();
    TestAccumulate();
    return 0;
}
