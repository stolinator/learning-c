#include <stdio.h>
#include <ctype.h>

// forward declaration
int can_print_it(char ch); // if you remove these lines, you'll need to reorganize the code
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
  int i = 0;

  for (i = 0; i < argc; i++) {
    print_letters(argv[i]);
  }
}

void print_letters(char arg[])
{
  int i = 0;

  for (i = 0; arg[i] != '\0';  i++) {
    char ch = arg[i];

    if (can_print_it(ch)) {
      printf("'%c' == %d ", ch, ch);
    }
  }

  printf("\n");
}

int can_print_it(char ch)
{
  return isalpha(ch) || isblank(ch) || isalnum(ch);
}

int main(int argc, char *argv[])
{
  print_arguments(argc, argv); // adding 1 to argc causes seg fault at runtime
  return 0;
}
