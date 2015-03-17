
#include <stdio.h>

int sum_func(int a, int b)
{
    return a + b;
}

struct Sum {
    int a;
    int b;
    int (*sum_func)(int, int);
};

int main(int argc, char *argv[])
{
    struct Sum s;
    int c;
    s.a = 10;
    s.b = 12;
    s.sum_func = sum_func;

    c = s.sum_func(s.a, s.b);
    // c = s.sum_func();
    printf("%d\n", c);

    // 给一个地址赋值
    *(unsigned int *)0x100000 = 1234;

    // 函数的强制转换
    void(*add_func)(int, int) = (void(*)(int,int))sum_func;
    void *p = &add_func;

    // 调用某个地址的函数
    (*((void(*)(int, int))p))(11, 13);

    return 0;
}
