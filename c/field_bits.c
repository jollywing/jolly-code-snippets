#include <stdio.h>
#include <stdlib.h>

int add_n(int n)
{
    static int i = 100;
    i += n;
    return i;
}

// What does ':' mean?
// d1 takes 5 bits
// d2 takes 14 bits
typedef struct _aa {
    int d1:5;
    int d2:14;
} AA;

struct bit {
    int a:3;
    int b:2;
    int c:3;
};

int main(int argc, char *argv[])
{
    int i;
    for(i = 0; i < 5; i++){
        printf("%d: %d\n", i+1, add_n(10));
    }

    AA a;
    printf("a.d1: %d; a.d2: %d\n", a.d1, a.d2);
    struct bit s;
    printf("The size of struct bit is %d\n", sizeof(struct bit));
    char *c = (char *)&s;
    *c = 0x99;

    // Linux下没有 itoa函数
    /* char str[32]; */
    /* itoa(*c, str, 2); */
    /* printf("The binary string of 99 is %s.\n", str); */

    printf("The Hex of 99 is %x.\n", *c);
    return 0;

}
