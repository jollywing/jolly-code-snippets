
/**
 * 问题： 给定数组 a[N]，其中有一个数是重复的，
 * 给出一个 O(N) 算法，找出这个重复的数。
 */

#include <time.h>
#include <stdio.h>

int get_repeat(int *a, int size)
{
    return 0;
}

int main(int argc, char *argv[])
{
    int a[100], i, r;
    srand(time(NULL));
    for(i = 0; i < 100; i++){
        a[i] = rand()%100;
    }
    a[98] = a[33];

    printf("The original array:");
    for(i = 0; i < 100; i++){
        if (i % 10 == 0) printf("\n");
        printf("%d ", a[i]);
    }

    r = get_repeat(a, 100);
    printf("%d\n", r);
    return 0;
}

