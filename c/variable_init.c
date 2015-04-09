/*
具有 “静态” 生存期的未初始化变量 (即, 在函数外声明的变量和有静态存储型的变量)
可以确保初始值为零, 就像程序员键入了 “=0” 一样。
如果是指针会被初始化为正确的空指针, 如果是浮点数会被初始化为 0.0。

具有 “自动” 生存期的变量 (即, 没有静态存储类型的局部变量) 如果没有显示
初始化, 则包含的是垃圾内容。对垃圾内容不能作任何有用的假设。

这些规则也适用于数组和结构 (称为 “聚合体” ); 对于初始化来说, 数组和结
都被认为是 “变量”。

用 malloc() 和 realloc() 动态分配的内存也可能包含垃圾数据,
因此必须由调用者正确地初始化。

用 calloc() 获得的内存为全零, 但这对指针和浮点值不一定有用。
*/

#include <assert.h>

/* a is a global var, its default value is 0 */
int a;

/* array is a global array, its elements are all inited as 0 by default. */
int array[10];

struct Circle {
    int x;
    int y;
    int radius;
};

struct Circle circle;

int main(int argc, char *argv[])
{
    /* c is a static var, so it has global property.
       its default value is also 0. */
    static char c;

    /* i is auto variable, its value is unknown. */
    short i;

    assert(a == 0);
    assert(c == 0);
    assert(array[0] == 0 && array[8] == 0);
    assert(circle.x == 0 && circle.y == 0 && circle.radius == 0);
    return 0;
}
