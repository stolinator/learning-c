#include<stdio.h>

struct Person {
  char *name;
  int age;
  int weight;
  int height;
};

struct Person Person_create(char *name,
    int age, int weight, int height)
{
  struct Person who;
  who.name = name;
  who.age = age;
  who.weight = weight;
  who.height = height;

  return who;
}

void Person_older(struct Person *who)
{
  who->age += 5;
}

void Person_print(struct Person who)
{
  printf("name: %s\n", who.name);
  printf("\tage: %d\n", who.age);
  printf("\tweight: %d\n", who.weight);
  printf("\theight: %d\n", who.height);
}

int main(int argc, char *argv[])
{
  struct Person joe = Person_create("Joe", 30, 160, 70);
  struct Person bubba = Person_create("Bubba", 26, 180, 67);
  Person_print(joe);
  Person_print(bubba);
  struct Person *joe_ptr = &joe;
  Person_older(joe_ptr);
  Person_print(joe);
}
