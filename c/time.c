
#include <stdio.h>
#include <time.h>
// #include <stdlib.h>

int main(int argc, char *argv[]) 
{
    // In fact time_t is a long integer type
    time_t cur_time;
    // return a integer reprensents current time.
    // 从1970年1月1日0时0分到当前时间经过的秒数
    // cur_time = time(NULL); or
    time(&cur_time);
    
    printf("%d seconds have passed since 1970-1-1 00:00\n", cur_time);
    // ctime 返回表示当前时间的字符串，该字符串包含换行符
    printf("Current time is %s", ctime(&cur_time));

    // struct tm is defined in <time.h>
    /*
      struct tm
      {
      int tm_sec;	
      int tm_min;	
      int tm_hour;	
      int tm_mday;	
      int tm_mon;	
      int tm_year;	
      int tm_wday;	
      int tm_yday;	
      int tm_isdst;	
    
      # ifdef	__USE_BSD
      long int tm_gmtoff;	
      const char *tm_zone;	
      # else
      long int __tm_gmtoff;	
      const char *__tm_zone;
      # endif
      };
    */
    struct tm * global_tm;
    // gmtime 和 localtime 返回的时间相差8小时
    // 如果你不是在中国，则时间差异又不是如此
    // 问题是，不论是 gmtime 还是 localtime，
    // 返回的日期需要处理。年 + 1900,
    // 月 (0-11) + 1
    global_tm = gmtime(&cur_time);
    printf("UTC time: %d-%d-%d %2d:%2d:%2d\n",
           global_tm->tm_year + 1900, global_tm->tm_mon + 1,
           global_tm->tm_mday, global_tm->tm_hour,
           global_tm->tm_min, global_tm->tm_sec);
    // gmtime 返回的结构体指针指向的是静态分配的结构体，
    // 不是在堆上分配的，所以不需要free
    // 如果你不保存这个结构体的值，不知何时它将被覆盖
    // free(global_tm); 运行时会报错

    struct tm local_tm;
    local_tm = *localtime(&cur_time);
    printf("Local time: %d-%d-%d %2d:%2d:%2d\n",
           local_tm.tm_year + 1900, local_tm.tm_mon + 1,
           local_tm.tm_mday, local_tm.tm_hour,
           local_tm.tm_min, local_tm.tm_sec);
    // free(local_tm);

    return 0;
    
}
