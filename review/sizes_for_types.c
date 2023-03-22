#include <stdio.h>

int main(int argc, char *argv[])
{
  /* char, unsigned char, signed char
   * int, unsigned int,
   * short, unsigned short
   * long, unsigned long
   */
  printf("char:\t%lu\n", sizeof(char));
  printf("usigned char:\t%lu\n", sizeof(unsigned char));
  printf("signed char:\t%lu\n", sizeof(signed char));

  printf("int:\t%lu\n", sizeof(int));
  printf("unsigned int:\t%lu\n", sizeof(unsigned int));

  printf("short:\t%lu\n", sizeof(short));
  printf("unsigned short:\t%lu\n", sizeof(unsigned short));

  printf("long:\t%lu\n", sizeof(long));
  printf("unsigned long:\t%lu\n", sizeof(unsigned long));
  return 0;
}
