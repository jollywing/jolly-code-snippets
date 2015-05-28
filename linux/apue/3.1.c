/* STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO. */

/* <fcntl.h> defines the constants: O_RDONLY, O_WRONLY, O_RDWR,
 * one and only one of them must be specified,
 * O_APPEND is optional.
 * O_TRUNC is also optional. If the file exists and if it is
 * successfully opened for either WRONLY or RDWR,
 * truncate its length to 0. */

/* int creat(const char *pathname, mode_t mode); is same to
 * open(pathname, O_WRONLY|O_CREAT|O_TRUNC, mode);
 * Today, a separate creat function is no longer needed. */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    fd = open("test.txt", O_WRONLY | O_TRUNC);
    if(fd >= 0)
        close(fd);
    /* printf("%d\n", STDIN_FILENO); */
    return 0;
}
