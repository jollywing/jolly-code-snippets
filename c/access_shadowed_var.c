#include <stdio.h>

int b = 0;

int main(int argc, char *argv[])
{
    int b = 10;
    int a;
    {
        /* shadow the local variable b */
        extern int b;
        a = b;
    }
    printf("local b: %d, global b: %d\n", b, a);
}
