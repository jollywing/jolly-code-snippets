#include <stdio.h>
#include <pthread.h>

/* 1. pthread_join的作用是什么？
 * 2. pthread_create 怎么传递多个参数？*/
/* gcc FILE_NAME -lpthread */
void* my_thread_func(void *id)
{
    int i;
    for(i = 0; i < 5; i ++){
        printf("Thread %d echo ...\n", *(int*)id);
        /* sleep 1 second */
        sleep(1);
    }
}

/* If my_thread_func has mutiple params, you need include them with a
 * structure. */
int main(int argc, char **argv)
{
    int i = 1, j = 2, ret = 0;
    pthread_t id1, id2;
    /* return 0 on success */
    ret = pthread_create(&id1, NULL, (void *)my_thread_func, &i);
    if(ret){
        printf("Create pthread error!\n");
        return -1;
    }

    ret = pthread_create(&id2, NULL, (void *)my_thread_func, &j);
    if(ret){
        printf("Create pthread error!\n");
        return -1;
    }

    int k;
    for(k = 0; k < 5; k++){
        printf("main thread echo ...\n");
        sleep(1);
    }

    /* wait pthread id1 to terminate. */
    /* 调用pthread_join后，主线程将阻塞，等待线程1结束 */
    pthread_join(id1, NULL);
    /* wait pthread id2 to terminate. */
    pthread_join(id2, NULL);
    return 0;
}
