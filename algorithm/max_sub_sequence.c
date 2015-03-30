
#include <time.h>
#include <stdio.h>

#define ARRAY_SIZE 10

// Find the sub sequence with the max sum
// in a given array containing positive integer and negative numbers.
// Input: (a: the integer array) (size: the size of a)
// output: (start: the start of sub sequence) (end: the end index of sub sequence)
// return: the max sum
int max_sub(int *a, int size, int *start, int *end)
{
    int i;
    int temp_sum = 0;
    int max = 0;
    int temp_start = 0;
    *start = 0;
    for(i = 0; i < size; i++){
        if(a[i] > 0 && temp_sum == 0){
            temp_start = i;
        }
        temp_sum += a[i];
        if(temp_sum > max){
            max = temp_sum;
            *start = temp_start;
            *end = i;
        }
        else if(temp_sum < 0)
            temp_sum = 0;
    }
    return max;
}

int main(int argc, char *argv[])
{
    // printf("%d\n", time(NULL));
    srand(time(NULL));

    // create a random sequence of integer
    int a[ARRAY_SIZE];
    int i;
    printf("The integer sequence is:\n");
    for(i = 0; i < ARRAY_SIZE; i++){
        a[i] = rand() % 20;
        if(a[i] < 12)
            a[i] = -a[i];
        printf("%d ", a[i]);
    }
    printf("\n");

    // find the sub sequence of max sum
    int max, start, end;
    max = max_sub(a, ARRAY_SIZE, &start, &end);
    printf("Find the sub sequence with max sum %d:\n", max);
    for(i = start; i <= end; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
