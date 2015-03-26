#include <stdio.h>

int main(int argc, char *argv[])
{
    /* a is pointer, who point to a integer array */
    int (*a)[10];

    int b[10] = {5, 0, 7, 9};
    a = &b;

    int i;
    for(i = 0; i < 5; i++)
        /* [] 的优先级比 * 高 */
        printf("%d ", (*a)[i]);

    printf("\n");
    return 0;
}
