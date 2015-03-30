//#include <conio.h>	//for use of getchar()
// conio.h is not a standard header, it is specific for dos platform.
//#include <curses.h> //for getch(). remember: gcc -lcurses ...
// curses is a graphic development libary for linux, its getch()
// is not same with windows'.
#include <stdio.h>	//for printf() and getchar()
#include <stdlib.h> //for system("xx")

#include <termios.h>  /* for tcxxxattr, ECHO, etc */
#include <unistd.h>   /* for STDIN_FILENO */

int getch();

int main(){
    char c;
    do{
        c = getch();
        if(c == 'c')
            // in windows, here should be system("cls")
            system("clear");
        else
            printf("your input is %c.\n", c);
    }while(c!='0');
    printf("program exit normally.\n");
    printf("\033[0;32m我能显示\033[4;31m彩色中文\033[0;32m字符！\033[0m\n");
}

// when you input a number, and RETURN,
// while loop twice, once for number, once for RETURN.
// how to solve?

//simulate windows' getch()
// it works!!
int getch (void){
    int ch;
    struct termios oldt, newt;
  
    // get terminal input's attribute
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    //set termios' local mode
    newt.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    //recover terminal's attribute
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  
    return ch;
}
