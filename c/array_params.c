
#include <stdio.h>

// 如果传入的数组第二维长度不同，会报警告错误。
void list_elements(int a[][5], int n)
{
    int i, j;
    for(i = 0; i < n; i++){
        for( j = 0; j < 5; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int some_array[10][4];
    list_elements(some_array, 10);
    return 0;
}
