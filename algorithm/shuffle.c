#include <stdio.h>

#define N 16


void main()
{
    int a[N];
    int i,j;
    int temp;

    for(i=0; i <N; i++)
        a[i] = i;

//srand((unsigned)time(NULL));

    for(i=0; i <N; i++)
    {
        j = rand()%N;

        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }


    for(i=0; i <N; i++)
        printf("%d ", a[i]);

    printf("\n");

    return;
}
