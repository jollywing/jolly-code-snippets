
/* 华为2007年7月面试题
 * What will be the output of the following C code? */
#include <stdio.h>

void main()
{
    int b = 3;
    int arr[] = {6, 7, 8, 9, 10};
    int *ptr = arr;
    *(ptr++) += 123;
    printf("%d, %d\n", *ptr, *(++ptr));
}

/* A. 8 8
 * B. 130 8
 * C. 7 7
 * D. 7 8
 *
 * The Answer is A.
 * 一开始我以为正确答案是D，但 printf 参数是从右向左压栈，
 * 先计算 ++ ptr，所以答案为A. */
