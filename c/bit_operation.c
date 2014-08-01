
#include <stdio.h>

void swap(int *x, int *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void shift_practice()
{
    char c[]= {0xf0, 0x0f, 0xcc, 0x55};
    int len = sizeof(c) / sizeof(char);
    int i;
    for(i = 0; i < len; i ++){
        printf("%d. 0x%.2x 0x%.2x\n", i + 1, c[i] << 3, c[i] >> 2);
    }
}

void bit_practice()
{
    int x = 0x98fdecba;
    printf("1. %x\n", x | 0xffffff00);
    printf("2. %x\n", x ^ 0x000000ff);
    printf("3. %x\n", x & 0xffffff00);
}

int main(int argc, char *argv[])
{
    shift_practice();

    bit_practice();

    unsigned int i;
    printf("Now, Input a hexadecimal number:\n");
    scanf("%x", &i);

    printf("It's decimal value is: ");
    printf("%d\n", i);

    printf("Its bit reversed result is: %x\n", ~i);

    printf("\n");

    int j, k;
    printf("Now input two hex number (seperated by space): ");
    scanf("%x%x", &j, &k);
    printf("Their decimal values are: %d %d\n", j, k);
    printf("Their bit and result is %x\n", j & k);
    printf("Their bit or result is %x\n", j | k);

    printf("Then I'll swap two number by exclusive-or operation\n");
    printf("Now, input two decimal number(seperated by space):\n");
    int x, y;
    scanf("%d%d", &x, &y);
    swap(&x, &y);
    printf("They become: %d and %d\n", x, y);
    return 0;
}
