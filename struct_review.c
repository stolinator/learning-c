#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Mug {
  char *name;
  char *color;
  int capacity;
  int max_volume;
  int weight;
};

struct Mug *Mug_create (char *name, char *color, int capacity, int max_volume, int weight) {

  struct Mug *mug = malloc( sizeof(struct Mug) );
  assert(mug != NULL);

  mug->name = strdup(name);
  mug->color = strdup(color);
  mug->capacity = capacity;
  mug->max_volume = max_volume;
  mug->weight = weight;

  return mug;
}

void Mug_destroy (struct Mug *mug)
{
  assert(mug != NULL);
  free(mug->name);
  free(mug->color);
  free(mug);
}

void Mug_print (struct Mug *mug)
{
  printf("Information for mug \"%s\":\n", mug->name);
  printf("\tcolor:\t%s\n", mug->color);
  printf("\tcurrent capacity:\t%d\n", mug->capacity);
  printf("\tmaximum volume:\t%d\n", mug->max_volume);
  printf("\tmug weight:\t%d\n", mug->weight);
  printf("---\n");
}

int main(int argc, char *argv[])
{
  struct Mug *black_rifle = Mug_create("black rifle", "black", 12, 0, 8);
  Mug_print(black_rifle);
  Mug_destroy(black_rifle);
  return 0;
}
