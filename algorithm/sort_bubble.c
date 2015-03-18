
#include <stdio.h>
#include <time.h>

void bubble_sort(int *a, int size);

int main(int argc, char *argv[])
{
  int a[20], i;
  srand(time(NULL));
  printf("The original array:\n");
  for(i = 0; i < 20; i++){
    a[i] = rand() % 100;
    printf("%d ", a[i]);
  }
  printf("\n");

  bubble_sort(a, 20);
  printf("The bubble sorted array:\n");
  for(i = 0; i < 20; i++){
    printf("%d ", a[i]);
  }
  printf("\n");

  return 0;
}

void bubble_sort(int *a, int size)
{
  int i, j;
  int t;
  for(i = 1; i < size; ++i){
    for(j = 0; j < size -i; ++j){
      if(a[j] > a[j+1]){
        t = a[j];
        a[j] = a[j+1];
        a[j+1] = t;
      }
    } // end for j
  }// end for i
}

void bubble_sort_enhanced(int *a, int size)
{
    int i, j, t;
    unsigned char swapped;
    for(i = 1; i < size; ++i) {
        swapped = 0;
        for(j = 0; j < size - i; ++j) {
            if(a[j] > a[j+1]){
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
                swapped = 1;
            }
        }
        if(!swapped)
            break;
    }
}
