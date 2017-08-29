
/* 1. 线程可以共享全局变量吗？ */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int a = 5;

void * create(void *arg)
{
    printf("New thread ...\n");
    /* New thread can share the global process data */
    printf("a = %d\n", a);
    return (void *)0;
}

int main(int argc, char* argv[])
{
    pthread_t pid;

    int ret = 0;
    a = a * a;
    ret = pthread_create(&pid, NULL, create, NULL);
    if(ret){
        printf("Create new thread failed!\n");
        return -1;
    }
    sleep(1);
    printf("New thread is created!\n");
    return 0;
}
