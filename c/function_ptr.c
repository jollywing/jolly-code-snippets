
#include <stdio.h>

#define GREEN 1
#define YELLOW 2
#define RED 3

#define SMALL 1
#define MEDIUM 2
#define LARGE 3

char leaf_color;
char leaf_size;

/* get_value is a function pointer  */
char (* get_value)();

/* get_value_func is a type of function pointer */
typedef char (*get_value_func)();

struct Item
{
    char value;
    get_value_func get;
};

int main(int argc, char *argv[])
{
    return 0;
}
