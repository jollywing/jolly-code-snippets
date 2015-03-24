
#include <assert.h>
#include <string.h>
#include <stdio.h>

int binary_search(void *array, size_t elem_size, size_t size, void *key){
    if(size <= 0) return -1;

    int low = 0;
    int high = size - 1;
    int mid, result;
    while(low <= high){
        mid = (low + high) / 2;
        result = memcmp(array + mid * elem_size, key, elem_size);
        if(result == 0) return mid;
        else if(result < 0){
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int result;

    int a[] = {100, 102, 104, 106, 108, 110};
    int int_key = 106;
    result = binary_search(a, sizeof(int), 6, &int_key);
    assert(result == 3);

    char s[] = "BCDEFGOPQ";
    char char_key = 'D';
    result = binary_search(s, sizeof(char), strlen(s), &char_key);
    assert(result == 2);

    return 0;
}
