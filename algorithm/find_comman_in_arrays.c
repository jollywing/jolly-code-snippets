#include <stdbool.h>
#include <stdio.h>

bool find_common_effective(int *a, int size_a, int *b, int size_b);
bool find_common(int *a, int size_a, int *b, int size_b);

int main(int argc, char *argv[])
{
  int a[100];
  int b[50];
  int i;

  for(i = 0; i < 100; i++) {
    a[i] = i * 2 + 1;
  }

  for(i = 0; i < 50; i++) {
    b[i] = i * 3;
  }

  find_common_effective(a, 100, b, 50);
  find_common(a, 100, b, 50);
  return 0;
}

bool find_common(int *a, int size_a, int *b, int size_b)
{
  int i, c=0;
  for(i = 0; i < size_b; i ++){
    int start = 0, mid, end= size_a - 1;

    // 对于排好序的数组使用二分查找法
    while(start <= end) {
      c++;

      mid = (start + end) / 2;
      if(b[i] == a[mid]){
        printf("NORMAL COMPARE TIME: %d\n", c);
        return true;
      }
      else if(b[i] > a[mid]){
        start = mid + 1;
      }
      else
        end = mid - 1;
    }
  }
  printf("NORMAL COMPARE TIME: %d\n", c);
  return false;
}

bool find_common_effective(int *a, int size_a, int *b, int size_b)
{
  int i=0, j=0;
  int c = 0;
  while(i < size_a && j < size_b){
    c++;

    if(a[i] == b[j]){
      printf("EFFECTIVE COMPARE TIME: %d\n", c);
      return true;
    }
    else if(a[i] < b[j])
      i++;
    else
      j++;
  }
  printf("EFFECTIVE COMPARE TIME: %d\n", c);
  return false;
}


