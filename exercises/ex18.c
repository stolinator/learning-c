#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  
  exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb) (int a, int b);
typedef int *(*sort_algo) (int *n, int c, compare_cb cmp);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int i = 0;
  int j = 0;
  int *target = malloc(count * sizeof(int));
  if (!target)
    die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  for (i = 0; i < count; i++) {
    for (j = 0; j < count - 1; j++) {
      if (cmp(target[j], target[j + 1]) > 0) {
        temp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = temp;
      }
    }
  }

  return target;
}

int *selection_sort(int *numbers, int count, compare_cb cmp)
{
  int *target = malloc(count * sizeof(int));
  if (!target)
    die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  int min_index = 0;
  int pos = 0;
  int cur = 0;
  int temp = 0;
  for (pos = 0; pos < count - 1; pos++) {
    min_index = pos;
    for (cur = pos + 1; cur < count; cur++) {
      if (cmp(target[min_index], target[cur]) > 0)
        min_index = cur;
    }
    temp = target[pos];
    target[pos] = target[min_index];
    target[min_index] = temp;
  }

  return target;
}

int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, sort_algo sort, compare_cb cmp)
{
  int i = 0;
  int *sorted = sort(numbers, count, cmp);

  if (!sorted)
    die("Failed to sort as requested");

  for (i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);
  unsigned char *data = (unsigned char *)cmp;
  for (i = 0; i < 25; i++) {
    printf("%02x:", data[i]);
  }
  printf("\n");
}

/*
int fake(int a, char b) {
  return 0;
}
*/

int main(int argc, char * argv[])
{
  if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers) die("Memory error.");

  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }
  compare_cb cmp[] = { sorted_order, reverse_order, strange_order };
  sort_algo sort[] = { bubble_sort, selection_sort };

  int j = 0;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      test_sorting(numbers, count, sort[i], cmp[j]);
    }
  }

  //test_sorting(numbers, count, selection_sort, sorted_order);

  //test_sorting(numbers, count, sorted_order);
  //test_sorting(numbers, count, fake);
  //test_sorting(numbers, count, NULL);
  //test_sorting(numbers, count, reverse_order);
  //test_sorting(numbers, count, strange_order);
  //test_sorting(numbers, count, bubble_sort, sorted_order);

  free(numbers);

  return 0;
}
