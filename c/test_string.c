
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[])
{

    char * s1 = "BeiJing";
    char * s2 = "BeiHai";
    assert(strncmp(s1, s2, 3) == 0);
    return 0;
}
