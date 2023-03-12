#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int a = 0;
  int b = 0;
  int result = 0;
  switch(argc) {
  case 3:
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    check(a, "You must supply correct integer value for <int a>!");
    check(b, "You must supply correct integer value for <int b>!");
    result = a & b;
    printf("bitwise AND of %d and %d is:\t%d\n", a, b, result);
    break;
  default:
    printf("bitwise_and: <int a> <int b>\n\trequires 2 arguments!!\n");
  }
  return 0;
error:
  return 1;
}
