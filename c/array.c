#include <string.h>
#include <assert.h>

void test_array_assign()
{
    int a[10] = {0};
    int b[10];
    int i;
    for(i = 0; i < 10; i++)
        b[i] = i * 3 + 1;

    /* error: array type 'int [10]' is not assignable */
    /* a = b; */

    memcpy(a, b, sizeof(b));
    for(i = 0; i < 10; i++)
        assert(a[i] == b[i]);
}

int main(int argc, char *argv[])
{
    test_array_assign();
    return 0;
}
