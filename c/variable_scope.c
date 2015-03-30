
#include <stdio.h>

char *version = "1.0.0";

void about()
{
  // version shadows the global version
  // How to access the latter.
  char *version;
  printf("Version: %s\n", version);
}

int main(int argc, char *argv[])
{
  about();
  return 0;
}
