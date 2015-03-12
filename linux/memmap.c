#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct person {
    size_t id;
    char name[16];
};

int main(int argc, char *argv[])
{
    struct person persons[20];
    /* open file records.dat */
    int fd = open("records.dat", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    /* write persons data to file */
    write(fd, persons, sizeof(struct person) * 20);
    /* close file descriptor */
    close(fd);
}
