#include <stdio.h>

void recursive_print(int lvl, char *msg)
{
  printf("%d: %s\n", lvl, msg);
  recursive_print(lvl + 1, msg);
}

int main(int argc, char *argv[])
{
  int level = 0;
  char *message = "a stack overflow is coming";
  recursive_print(level, message);
  return 0;
}
