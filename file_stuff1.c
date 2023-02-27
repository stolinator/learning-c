#include <stdio.h>
#include <stdlib.h>

/* read and print contents of a text file */

/* this was done really badly and has memory leaks */
int main(int argc, char *argv[])
{
  char *filename = "hello.txt";
  FILE *textfile = fopen(filename, "r");
  // how do you know how much memory to allocate when reading file?
  //char *message;
  char *message = malloc(sizeof(char) * 100);
  fread(message, sizeof(char) * 13, 1, textfile);
  printf("The message was: %s\n", message);
  free(message);
  return 0;
}
