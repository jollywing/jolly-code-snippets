
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else  /* LINUX */
#include <system.h>
#endif

int main(int argc, char *argv[])
{
  int sec;
  // scanf("Input a integer: %d", &sec);
  printf("Input a integer representing sec: ");
  scanf("%d", &sec);
  while(1) {
#ifdef _WIN32
    // on windows XP
    Sleep(sec * 1000);
#else
    // sleep(int sec), or
    delay(sec * 1000);
#endif
    printf("%d seconds passed.\n", sec);
  }
}
