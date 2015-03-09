#include <stdio.h>
#include <time.h>

void test_clock()
{
    /* Returns elapsed processor time used by program or -1 if not available. */
    clock_t cpu_time = clock();
    printf("Elapsed clock: %d\n", cpu_time);
}

void test_time_func()
{
    time_t cur_time = time(NULL);
    /* Get time string from time_t */
    printf("ctime result: %s\n", ctime(&cur_time));
    /* return pointer to struct tm */
    struct tm * universal_time = gmtime(&cur_time);
    printf("gmtime result: %s\n", asctime(universal_time));
    /* local time is 8 hours earlier than gm time result  */
    struct tm * local_time = localtime(&cur_time);
    printf("localtime result: %s\n", asctime(local_time));
}

void test_strftime()
{
    char fmt_result[128];
    const char * TIME_FORMAT = "%Z %x %X";
    struct tm * cur_time;
    /* Get a time struct representing current time */
    time_t cal_time = time(0);
    cur_time = localtime(&cal_time);
    /* get the formatted time string */
    strftime(fmt_result, 128, TIME_FORMAT, cur_time);
    /* output timestring */
    printf("Formatting result: %s\n", fmt_result);
}

int main(int argc, char *argv[])
{
    test_time_func();
    test_strftime();
    test_clock();
    return 0;
}
