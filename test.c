#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void func(int *a)
{
  *a += 1;
}
int main()
{
  int a = 5;
  func(&a);
  printf("%d\n", a);
}
