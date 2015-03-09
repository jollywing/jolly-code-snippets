#include <stdio.h>

void test_FILE_LINE()
{
    printf("Current Location: %s:%d\n", __FILE__, __LINE__);
}

int main(int argc, char *argv[])
{
    test_FILE_LINE();
    return 0;
}
