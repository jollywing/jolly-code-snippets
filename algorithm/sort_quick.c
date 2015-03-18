
/* @purpose: This program shows how to use `qsort' function in stdlib.h
 * @author: jollywing@foxmail.com
 * */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cmp_float(const void * f1, const void *f2){
    float n1 = *((float *)f1);
    float n2 = *((float *)f2);
    if(n1 == n2)
        return 0;
    else if(n1 < n2)
        return -1;
    else
        return 1;
}

int cmp_char(const void *p1, const void *p2)
{
    char a = *((char *)p1);
    char b = *((char *)p2);
    if(a == b) return 0;
    else if(a < b) return -1;
    else return 1;
}

int main()
{
    float a[] = {0.005, 1.00, -5.0, -22.11, 100.02, 3.0f};
    qsort(a, 6, sizeof(float), cmp_float);
    int i = 0;
    for(i = 0; i < 6; i++)
        printf("%.3f ", a[i]);
    printf("\n");

    char s[] = "Hello, the world!";
    qsort(s, strlen(s), sizeof(char), cmp_char);
    printf("%s\n", s);
    return 0;
}
