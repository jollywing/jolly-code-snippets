
/* USAGE: Read commands from stdin and execute them,
 * which will catch SIGINT without quiting. */

/* Signals are a technique used to notify a process
 * that some condition occurred. */

#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);       /* our signal catching func */

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    /* The behavior  of signal()  varies across UNIX  versions, and
     * has also  varied historically  across different  versions of
     * Linux.   Avoid  its  use:  use  sigaction(2)  instead. */
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        }
        else if(pid == 0) {     /* child process */
            execlp(buf, buf, (char *)0);
            err_ret("could not execute: %s", buf);
            exit(127);
        }

        /* parent process */
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("interrupt key sequence is invalid\n%% ");
}
