#include <windows.h>
#include <wincon.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO bInfo;
  GetConsoleScreenBufferInfo(hOut, &bInfo);
  COORD pos = {0, 0};
  FillConsoleOutputCharacter(hOut, '@', bInfo.dwSize.X / 2 * bInfo.dwSize.Y, pos, NULL);
  CloseHandle(hOut);
}
