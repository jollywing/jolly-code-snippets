#include <stdio.h>

void test_char_pointer()
{
    char *c= "Hello";
    printf("%c\n", *c);
}

void test_pointer()
{
    /* char *av[] = {"HH", "mm", "I like"}; */
    char *av[5];
    /* av is a const pointer, can not changed: lvalue required as increment operand */
    /* av++; */
    char **p = av;
    printf("%s\n", *++p);
    printf("%s\n", av[1]);
}

int main(int argc, char *argv[])
{
    test_pointer();
    test_char_pointer();
    return 0;
}
