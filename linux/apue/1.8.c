/* USAGE: Demonstrate strerror and perror */

#include "apue.h"
#include <errno.h>

/* The errors defined in <errno.h> can devided into 2 categories:
 * fatal and nonfatal. When we deal with nonfatal errors,
 * we need not exit the program, for examble, as to resource related
 * nonfatal errors, we can delay a bit and try again. */
int main(int argc, char *argv[])
{
    /* strerror, need <string.h> */
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));

    errno = ENOENT;
    /* perror: need <stdio.h> */
    perror(argv[0]);
    return 0;
}
