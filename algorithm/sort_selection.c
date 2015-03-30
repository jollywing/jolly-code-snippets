#include <stdio.h>

void sel_sort(int *a, size_t size)
{
    int i, j;
    int min_index;
    int t;
    for(i = 0; i < size - 1; i ++){
        min_index = i;
        for( j = i + 1; j < size; j++){
            if(a[j] < a[min_index])
                min_index = j;
        }
        if (min_index != i){
            t = a[i];
            a[i] = a[min_index];
            a[min_index] = t;
        }
    }
}

int main(int argc, char *argv[])
{
    int i;
    int a[] = {9, 8, 10, 55, 2, -22};
    int size = sizeof(a) / sizeof(int);
    sel_sort(a, size);
    for(i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
