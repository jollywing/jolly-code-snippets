#include <stdio.h>
#include <stdlib.h>

/* convert string to integer */
int atoi(const char *s)
{
    int signal = 1;
    int result = 0;
    const char *p = s;

    /* skip space */
    while(isspace(*s))
        ++s;

    if(*s == '-' || *s == '+'){
        if(*s == '-')
            signal = -1;
        s++;
    }
    while(isdigit(*s) && *s != '\0'){
        result = result * 10 + (*s - '0');
        s++;
    }
    if(*s != '\0'){
        printf("Your input (%s) is not a valid digital string!\n", p);
        exit(1);
    }

    result = result * signal;
    return result;
}

int main(int argc, char *argv[])
{
    int i, j, k;
    i = atoi("-12345");
    j = atoi("+567890");
    k = atoi("--11");
    printf("%d %d\n", i, j);
    return 0;
}
