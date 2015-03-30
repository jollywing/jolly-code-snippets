#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int i;
    if(fork() == 0){
        /* fork函数对子进程返回0, 所以这是子进程执行的代码 */
        /* 子进程复制了父进程的堆栈和数据段，所以子进程的变量i不会影响父进程的i */
        for (i = 0; i < 100; i++){
            printf("%d: child process.\n", i);
        }
    }
    else {
        /* 对于父进程来说，fork函数返回子进程的id */
        for (i = 0; i < 100; i++){
            printf("%d: main process.\n", i);
        }
    }
    return 0;
}
