
#include <stdio.h>

const char *version = "1.0.0";

void about()
{
  // version shadows the global version
  // How to access the latter.
  char *version;
  // In c++, you can use '::' to access a global variable
  printf("Version: %s\n", ::version);
}

int main(int argc, char *argv[])
{
  about();
  return 0;
}
