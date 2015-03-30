
#include <stdio.h>

/* int inArray(void *value, void *array, int len) */
/* { */
/*     int i; */
/*     for(i=0; i<len; i++) */
/*         if(*value == array[i]) */
/*             return i; */

/*     return -1; */
/* } */

int in_array(const void *arr, int arr_len, const void *elem, int elem_size)
{
    int i;
    const void *p = arr;
    for (i = 0; i < arr_len; i++, p += elem_size)
        if (memcmp(p, elem, elem_size) == 0)
            return i;
    return -1;
}

int main(int argc, char *argv[])
{
    char aa[64] = "I like this.";
    char a = 'l';
    printf("%d\n", in_array(aa, 5 * sizeof(a), &a, sizeof(a)));
    return 0;
}
