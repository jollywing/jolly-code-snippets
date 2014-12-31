
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

void test_string_copy()
{
    char s[3];
    strcpy(s, "Hello");
    /* pass, output: Hello, but the string value will be changed */
    printf("%s\n", s);

    char *ds = (char *)malloc(3);
    strcpy(ds, "hello");
    /* also pass! output: hello */
    printf("%s\n", ds);
    free(ds);

    char ss[12];
    strncpy(ss, "world", 6);
    assert(ss[5] == 0);
}

void test_string_contain_zero(){
    /* "Hello" is a string terminated with 0 */
    char m[10] = "Hello";
    assert(m[5] == 0);          /* PASS */
}

int main(int argc, char *argv[])
{

    char * s1 = "BeiJing";
    char * s2 = "BeiHai";
    assert(strncmp(s1, s2, 3) == 0);

    test_change_string();
    test_string_copy();
    test_string_contain_zero();
    return 0;
}
