
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* press C-d to exit this function */
void read_char()
{
    char c;
    char prompt[32] = "Input a char:\n";
    /* STDOUT_FILENO is the file descriptor of STDOUT */
    /* printf("%s", prompt) */
    /* fprintf(stdout, "%s", prompt) */
    write(STDOUT_FILENO, prompt, strlen(prompt));
    while(read(STDIN_FILENO, &c, 1) > 0){
        write(STDOUT_FILENO, &c, 1);
    }
}

void read_line()
{
    char line[256];
    int n;
    char prompt[32] = "INPUT a STRING:\n";
    write(STDOUT_FILENO, prompt, strlen(prompt));
    while((n = read(STDIN_FILENO, line, 256)) > 0){
        write(STDOUT_FILENO, line, n);
    }
}

void test_create_on_nonexist()
{
    int fd;
    /* if demo.txt is nonexisting, then create it */
    fd = open("demo.txt", O_RDONLY|O_CREAT|O_APPEND, 0);
    close(fd);
}

void read_file_content()
{
    /* open(const char *pathname, int flags, mode_t mode); */
    /* 如果 flags 中有 O_CREATE, 必须提供mode参数，用于指定新文件的权限, 这
     * 个权限只会影响将来的访问，不会影响这次的文件描述符。 */
    int fd = open("demo.txt", O_RDONLY, 0);
    if(fd < 0){
        printf("Open demo.txt failed!\n");
        return;
    }

    char buf[256];
    ssize_t nread;
    memset(buf, 0, 256);
    /* return the bytes readed.
     * If EOF has been reached, read return 0
     */
    nread = read(fd, buf, 255);
    printf("%d bytes readed!\n", nread);
    printf("%s\n", buf);

    close(fd);

    int i;
    printf("[");
    for(i = 0; i <= strlen(buf); i++){
        printf("%d ", buf[i]);
    }
    printf("]\n");
    
}

void get_file_meta_data(const char* filename)
{
    struct stat st;
    char * filetype;
    char * readok, *writeok;

    /* fill struct stat */
    stat(filename, &st);

    if(S_ISREG(st.st_mode))
        filetype = "Regular";
    else if(S_ISDIR(st.st_mode))
        filetype = "Directory";
    else if(S_ISSOCK(st.st_mode))
        filetype = "Socket";
    else
        filetype = "Unknown";

    if(st.st_mode & S_IRUSR)
        readok = "Yes";
    else
        readok = "No";
    if(st.st_mode & S_IWUSR)
        writeok = "Yes";
    else
        writeok = "No";

    printf("filename: %s; type: %s; "
            "readable: %s; writable: %s\n",
            filename, filetype, readok, writeok);
}

void open_same_file_again(const char *filename)
{
    printf("========== OPEN SAME FILE ==========\n");
    /* There will be 2 items in the <descriptor talbe> */
    /* There will be 2 items in the <file table> with different locations */
    int fd1 = open(filename, O_RDONLY, 0);
    int fd2 = open(filename, O_RDONLY, 0);
    char c;
    read(fd1, &c, 1);
    read(fd2, &c, 1);
    printf("%c\n", c);
    close(fd1);
    close(fd2);
}

void fork_read(const char *filename)
{
    printf("========== FORK READ ==========\n");
    int fd = open(filename, O_RDONLY, 0);
    char c;
    if(fork() == 0){
        read(fd, &c, 1);
        exit(0);
    }
    wait(NULL);
    read(fd, &c, 1);
    printf("%c\n", c);
    close(fd);
}

void test_dup2(const char *filename)
{
    printf("========== I/O redirection ==========\n");

    int fd1 = open(filename, O_RDONLY, 0);
    int fd2 = open(filename, O_RDONLY, 0);
    char c;
    read(fd2, &c, 1);
    printf("%c\n", c);

    /* redirect fd1 to fd2 */
    /* copy record indexed by fd2 to record indexed by fd1 */
    /* Thus fd1 will point to the file pointed by fd2 */
    dup2(fd2, fd1);
    read(fd1, &c, 1);
    printf("%c\n", c);

    int result;
    result = close(fd2);
    result = close(fd1);
    if(result < 0){
        printf("close file descriptor failed!\n");
    }
}

int main(int argc, char * argv[])
{
    read_char();
    read_line();
    read_file_content();
    get_file_meta_data("demo.txt");
    open_same_file_again("demo.txt");
    fork_read("demo.txt");
    test_dup2("demo.txt");
    return 0;
}
