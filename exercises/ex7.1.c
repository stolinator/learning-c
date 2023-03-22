#include<stdio.h>

int main(int argc, char *argv[])
{
  char nul_byte = '\0';
  printf("using %%d:\t%d\n", nul_byte);
  //printf("using %%s:\t%s\n", nul_byte);
  printf("using %%c:\t%c\n", nul_byte);
  return 0;
}
