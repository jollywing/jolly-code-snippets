#include <pthread.h>
#include <stdio.h>

void *create(void *arg)
{
    printf("New thread .... \n");
    printf("This thread's id is %u\n", (unsigned int)pthread_self());
    printf("The process pid is %d\n",getpid());
    return (void *)0;
}

int main(int argc, char *argv[])
{
    pthread_t pid;
    int ret = 0;
    ret = pthread_create(&pid, NULL, create, NULL);
    if(ret){
        printf("Creating thread failed!\n");
        return -1;
    }
    pthread_join(pid, NULL);
    printf("The process pid is %d\n", getpid());
    return 0;
}
