#include <stdio.h>

void insertion_sort(int *a, size_t size)
{
    int i, j, t;
    for(i = 1; i < size; i++){
        t = a[i];
        j = i - 1;
        while(j >= 0){
            if(a[j] > t){
                a[j + 1] = a[j];
            }
            else
                break;
            j--;
        }
        j += 1;
        a[j] = t;
    }
}

int main(int argc, char *argv[])
{
    int i;
    int a[] = {9, 8, 10, 55, 2, -22};
    int size = sizeof(a) / sizeof(int);
    insertion_sort(a, size);
    for(i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
