#include <stdio.h>

int main(int argc, char *argv[])
{
    /* C99 defined `long long' type, it includes at least 8 bytes. */
    long long i;
    long j;
    int k;
    printf("long long size: %d; long size: %d; int size: %d\n",
            sizeof(i), sizeof(j), sizeof(k)); /* 8, 4, 4 */
    return 0;
}
