
class Test {
public:
    Test(int){}
    Test(){}
    void fun() {}
};

int main()
{
    Test a(1);
    a.fun();
    // 如果b使用默认构造函数，一定不能使用Test b();而是使用 Test b;
    // Test b(); 会把b声明为一个函数。
    Test b;
    b.fun();
}
