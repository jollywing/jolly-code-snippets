#include <stdio.h>

#define     min(a, b)    ((a) < (b)? (a) : (b))
#define     max(a, b)    ((a) < (b)? (b) : (a))

#define SWAP(a,b)                               \
    int t = a;                                  \
    a = b;                                      \
    b = t;

int main(int argc, char *argv[])
{
    int result = max(5, 5+2) * 2;
    printf("%d\n", result);

    int a = 10;
    int b = 15;
    printf("BEFORE SWAP, a = %d, b = %d\n", a, b);
    SWAP(a, b);
    printf("AFTER SWAP, a = %d, b = %d\n", a, b);

    return 0;
}
