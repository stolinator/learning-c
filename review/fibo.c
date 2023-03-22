#include <stdio.h>
#include <stdlib.h>

long fibo(long n)
{
  if ((n == 0) || (n == 1)) {
    return 1;
  } else {
    return fibo(n - 2) + fibo(n -1);
  }
}

int main(int argc, char *argv[])
{
  if (argc > 1) {
    long n = atoi(argv[1]);
    printf("%ld\n", fibo(n));
  } else {
    printf("fibo <n>\n");
    printf("----------\n");
    printf("\tcomputes the nth term of the fibonacci sequence\n");
    printf("\t<n>\tan integer representing the nth term to compute\n");
  }
  return 0;
}
