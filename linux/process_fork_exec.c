#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

char command[256];

int main(int argc, char *argv[])
{
    int rtn;
    while(1){
        printf(">");
        fgets(command, 256, stdin);
        command[strlen(command) - 1] = 0;
        // printf("your command: %s\n", command);

        if(fork() == 0) {
            execlp(command, command);
            perror(command);
            exit(errno);
        }
        else {
            wait(&rtn);
            printf("Child process return %d\n", rtn);
        }
    }
    return 0;
}
