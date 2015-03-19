/* 本程序示范互斥锁的应用 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/* set gold value int box */
int money = 100000;
void* get_money(void *deposit);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
    int p1_money = 0;
    int p2_money = 0;
    int p3_money = 0;

    pthread_t p1_thread, p2_thread, p3_thread;

    int ret = 0;

    srand(time(NULL));

    /* create thread 1 */
    ret = pthread_create(&p1_thread, NULL, get_money, &p1_money);
    if(ret != 0){
        perror("p1 thread create error!");
        exit(EXIT_FAILURE);
    }
    /* create thread 2 */
    ret = pthread_create(&p2_thread, NULL, get_money, &p2_money);
    if(ret != 0){
        perror("p2 thread create error!");
        exit(EXIT_FAILURE);
    }
    /* create thread 3 */
    ret = pthread_create(&p3_thread, NULL, get_money, &p3_money);
    if(ret != 0){
        perror("p3 thread create error!");
        exit(EXIT_FAILURE);
    }

    /* wait threads to end */
    pthread_join(p1_thread, NULL);
    pthread_join(p2_thread, NULL);
    pthread_join(p3_thread, NULL);

    printf("p1 get %d;\n", p1_money);
    printf("p2 get %d;\n", p2_money);
    printf("p3 get %d;\n", p3_money);
    printf("total: %d.\n", p1_money + p2_money + p3_money);
    return 0;
}

/* 抢钱的进程， */
void * get_money(void *deposit)
{
    int money_got_each_time;
    while(money > 0){
        if(pthread_mutex_lock(&mutex) != 0){
            perror("pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }
        money_got_each_time = rand() % 10;
        if (money < money_got_each_time)
            money_got_each_time = money;
        money -= money_got_each_time;
        *((int *)deposit) += money_got_each_time;
        // usleep(1);
        if(pthread_mutex_unlock(&mutex) != 0){
            perror("pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }
    }
}
