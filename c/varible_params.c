
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

void cat_strings(char *result, int n, ...)
{
    va_list arg_pointer;
    va_start(arg_pointer, n);
    while(n--){
        char *s;
        s = va_arg(arg_pointer, char *);
        strcat(result, s);
    }
    
}

int main(int argc, char *argv[])
{
    char message[1024];
    memset(message, 0, sizeof(message));
    cat_strings(message, 4, "I love ", "his ", "dark ", "hair.");
    printf("%s\n", message);
    return 0;
}
