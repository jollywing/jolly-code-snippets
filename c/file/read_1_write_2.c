
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char strs[3][16];
  // printf("%d\n", sizeof(strs));

  memset(strs, '\0', sizeof(strs));
  fp = fopen("file1.txt", "r");
  char c;
  char i = 0, j = 0;
  while((c = fgetc(fp)) != EOF){
    if(c == '\n' || c == '\r'){
      if(j > 0){
        i++;
        j = 0;
      }
    }
    else {
      strs[i][j] = c;
      j ++;
    }
  }
  fclose(fp);

  fp = fopen("file2.txt", "w");
  for(i = 2; i >=0; i--){
    fputs(strs[i], fp);
    fputc('\n', fp);
  }
  fclose(fp);
  return 0;
}
