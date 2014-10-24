
#include <pthread.h>
#include <stdio.h>

void *create(void *arg)
{
    printf("new thread is created.\n");
    return (void *)8;
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t pid;
    void *temp;

    ret = pthread_create(&pid, NULL, create, NULL);
    if(ret){
        printf("Creating thread failed!\n");
        return -1;
    }

    /* pthread_join can get the exit code of the joined thread */
    ret = pthread_join(pid, &temp);
    if(ret){
        printf("Joining thread error!\n");
        return -2;
    }

    printf("The thread returns exit code: %d\n", (long)temp);
    return 0;
}
