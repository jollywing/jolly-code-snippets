#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int getch(void) 
{ 
    struct termios tm, tm_old; 
    int fd = STDIN_FILENO, c; 

    if(tcgetattr(fd, &tm) < 0) 
        return -1; 

    tm_old = tm; 

    cfmakeraw(&tm); 

    if(tcsetattr(fd, TCSANOW, &tm) < 0) 
        return -1; 

    c = fgetc(stdin); 

    if(tcsetattr(fd, TCSANOW, &tm_old) < 0) 
        return -1; 

    return c; 
} 

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[2048];
    /* int c; */
    fp = fopen("1.txt", "w");

    do{
        buf[0] = '\0';
        fgets(buf, 2048, stdin);
        fputs(buf, fp);
    } while(!feof(stdin));
    fclose(fp);
    return 0;
}
