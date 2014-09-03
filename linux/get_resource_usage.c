
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>

void test_getrusage()
{
    /* int getrusage(int who, struct rusage *usage) */
    /* who can be RUSAGE_SELF (calling process),
    * RUSAGE_CHILDREN (all children), RUSAGE_THREAD (calling thread)*/
    /* man getrusage to see the definition of struct rusage */

    struct rusage info;
    if(getrusage(RUSAGE_SELF, &info) < 0){
        printf("Get resource usage info failed!\n");
        exit(1);
    }

    printf("user CPU time: %d sec, %d usec\n", info.ru_utime.tv_sec,
        info.ru_utime.tv_usec);
    printf("Sys CPU time: %d sec, %d usec\n", info.ru_stime.tv_sec,
            info.ru_stime.tv_usec);
    printf("Stack Size: %d\n", info.ru_isrss);
    printf("page faults: %d\n", info.ru_majflt);
}

int main(int argc, char *argv[])
{
    test_getrusage();
    return 0;
}
