#include <stdio.h>

#define MAX_BITS 10

int main(int argc, char *argv[])
{
    int i;
    scanf("%d", &i);
    int bits[MAX_BITS] = {0};
    int bit_count = 0;
    while( i > 0){
        bits[bit_count] = i % 10;
        bit_count++;
        i /= 10;
    }

    int reversed_num = 0;
    for(i = 0; i < bit_count; i++) {
        reversed_num = reversed_num * 10 + bits[i];
    }
    printf("%d\n", reversed_num);
    return 0;
}
