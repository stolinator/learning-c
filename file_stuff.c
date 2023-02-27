#include <stdio.h>

/* create a plain text file with hello world in it */

int main(int argc, char *argv[])
{
  char *message = "Hello, World!";
  char *filename = "hello.txt";
  FILE *textfile = fopen(filename, "w");

  // can't use sizeof on a pointer, it returns incorrect size
  //printf("size of message is %ld\n", sizeof(message));
  int i = 0;
  for (i = 0; message[i] != '\0'; i++) {
  }
  printf("size of message is %d\n", i);


  int rc = fwrite(message, sizeof(char) * i, 1, textfile);

  printf("rc was: %d\n", rc);
  fclose(textfile);
  printf("File written!\n");

  return 0;
}
