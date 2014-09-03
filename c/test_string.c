
#include <string.h>
#include <assert.h>
#include <stdio.h>

void test_change_string()
{
    char *s;
    s = "I'm Ok";
    printf("%s\n", s);

    /* You can not, s point to const */
    /* strcpy(s, "How are you"); */
    /* strcat(s, ";"); */

    s = "Nice Day";
    printf("%s\n", s);
    s = "Shit of you!";
    printf("%s\n", s);
}

int main(int argc, char *argv[])
{

    char * s1 = "BeiJing";
    char * s2 = "BeiHai";
    assert(strncmp(s1, s2, 3) == 0);

    test_change_string();
    return 0;
}
