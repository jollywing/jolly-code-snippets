
/* !!! man 7 aio to view the functions and aiocb structure */
/* gcc aio.c -lrt; -lrt is important */
/* AIO need aio.h */
#include <aio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BUFSIZE 1024

void test_aio_read_file();
void test_aio_write_file();

int main(int argc, char *argv[])
{
    test_aio_write_file();
    test_aio_read_file();
    return 0;
}

void test_aio_write_file()
{
    /* aio control block */
    struct aiocb my_aiocb;
    /* bzero(char *buf, size_t size); need <strings.h> */
    bzero((char *)&my_aiocb, sizeof(struct aiocb));
    /* 为AIO分配空间 */
    my_aiocb.aio_buf = malloc(BUFSIZE + 1);
    if(!my_aiocb.aio_buf){
        perror("malloc aio buffer failed!\n");
        return;
    }

    const char src_str[256] = "Oh my god!\n";
    strcpy((char *)my_aiocb.aio_buf, src_str);
    my_aiocb.aio_nbytes = strlen(src_str) + 1;
    my_aiocb.aio_offset = 0;

    int fd;
    /* 打开文件，如果成功，返回一个不小于0的描述符 */
    fd = open("demo.txt", O_APPEND);
    if(fd < 0){
        perror("Open file failed!\n");
        return;
    }
    /* 为AIO设置文件描述符 */
    my_aiocb.aio_fildes = fd;

    int ret;
    /* 缓冲区和对应的文件描述符都已经设置好，可以写入 */
    /* 如果排队成功，立即返回0，如果失败返回 -1 */
    ret = aio_write(&my_aiocb);
    if(ret < 0){
        perror("Enqueue AIO write request failed!\n");
        close(fd);
        return;
    }

    /* 查询AIO的状态 */
    while(aio_error(&my_aiocb) == EINPROGRESS);

    if((ret = aio_return(&my_aiocb)) <= 0){
        perror("AIO write failed!\n");
        /* strerr need string.h */
        strerror(errno);
    }

    close(fd);
}

void test_aio_read_file()
{
    /* how to create aiocb */
    struct aiocb my_aiocb;
    bzero((char *)&my_aiocb, sizeof(struct aiocb));
    /* malloc need stdlib.h */
    my_aiocb.aio_buf = malloc(BUFSIZE + 1);
    if(!my_aiocb.aio_buf){

        /* perror: print a system error message
         * #include <stdio.h>
         * void perror(const char *s); */
        perror("malloc aio buffer failed!\n");
        return;
    }

    int fd;
    /* man 2 open, return -1 if an error occured */
    fd = open("demo.txt", O_RDONLY);
    if(fd < 0){
        perror("Open file failed!\n");
        return;
    }

    /* fildes = file descriptor */
    my_aiocb.aio_fildes = fd;
    my_aiocb.aio_offset = 0;    /* 从头开始读 */
    my_aiocb.aio_nbytes = BUFSIZE;

    int ret;
    /* enqueue a read request */
    /* link with -lrt? */
    /* aio_read: return 0 on success, return -1 on error and the request is
     * not enqueued */
    ret = aio_read(&my_aiocb);
    if (ret < 0){
        perror("AIO read error!\n");
        close(fd);
        return;
    }

    /* if the request has not been completed yest, then wait */
    /* notice: EINPROGRESS need <errno.h> */
    while(aio_error(&my_aiocb) == EINPROGRESS);

    /* return bytes readed on success */
    if((ret = aio_return(&my_aiocb)) > 0){
        printf("%s\n", (char *)my_aiocb.aio_buf);
    }
    else {
        perror("AIO read failed!\n");
    }
    close(fd);
}
