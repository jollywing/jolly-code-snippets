/* 1.6 Print the process ID */
/* 1.7 Read commands from standard input and execute them */
#include "apue.h"
#include <sys/wait.h>

/* There are three primary functions for process control: fork exec waitpid */
int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");               /* print command prompt */

    /* When we type C-d, fgets return null, exit this main loop */
    /* When we type Enter, fgets fill buf with what we typed,
     * include the new line character and \0 */
    while(fgets(buf, MAXLINE, stdin) != NULL){
        /* replace the new line character with '\0' */
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        /* fork to create a process
         * fork return non-negative process ID of new child process
         * to the parent, and return 0 to the child process.
         * for is called once and return twice in the parent and in the child */
        if ((pid = fork()) < 0) {
            err_sys("fork error!\n");
        }
        else if (pid == 0) {
            /* This is child process */

            /* Execlp replace the child process with new program file */
            /* fork then exec, is what some OS call spawning a new process */
            execlp(buf, buf, (char *)0);
            err_ret("could not execute: %s\n", buf);
            exit(127);
        }

        /* parent process*/
        /* wait for child process to terminate.
         * waitpid also returns the termination status of the child */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("wait pid error!\n");
        printf("%% ");
    }

    /* getpid() return ID of this process */
    printf("\nBye! from process ID %d\n", getpid());
    exit(0);
}
