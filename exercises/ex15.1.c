#include<stdio.h>

/* write a for loop that uses a pointer to iterate
 * through an array of strings
 */

int main(int argc, char *argv[])
{
  char *names[] = {
    "Larry", "Curly", "Moe"
  };

  int i = 0;
  
  /* the ways
   * 1. just enumerate indexes of arrays ary[i]
   * 2. create pointer to start of array *(ptr_ary + i)
   * 3. pointers are just arrays ptr_ary[i]
   */

  // one way
  int sizeof_names = printf("%lu\n", sizeof(names) / sizeof(char *));
  for (i = 0; i <= sizeof_names; i++) {
    printf("%d:\t%s\n", i, *(names + i));
  }

  // another way
  char **current_name = names;
  for (i = 0; i <= sizeof_names; i++) {
    printf("%d:\t%s\n", i, current_name[i]);
  }

  return 0;
}
