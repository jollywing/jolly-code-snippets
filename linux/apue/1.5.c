/* Copy stdin to stdout, using standard IO */
/* gcc 1.5.c error.c */

#include "apue.h"

int main(void)
{
    int c;
    while((c = getc(stdin)) != EOF)
        /* putc: EOF on error */
        if(putc(c, stdout) == EOF)
            err_sys("output error");

    /* If there is some error, return non-zero value */
    if(ferror(stdin))
        err_sys("input error");

    exit(0);
}
