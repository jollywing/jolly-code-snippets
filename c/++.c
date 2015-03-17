#include <stdio.h>

#define SQUARE(a)((a)*(a))

int main(int argc, char *argv[])
{
    int a=5;
    int b;
    b=SQUARE(a++);
    printf("%d\n",b); // 5*6 = 30
    //a = 7

    b=SQUARE(++a); // 9 * 9 = 81
    printf("%d\n",b);
    return 0;
}
