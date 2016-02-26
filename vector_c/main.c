#include <stdio.h>
#include <time.h>
#include "vector.h"

int main () {
  time_t start = time(NULL);
  struct vector v;
  init(&v);
  long int n = 100;
  for (long int i = 0; i < n; ++i) {
    push_back(&v, (i - 1) * (i + 1));
  }
  for (long int i = 0; i < n; ++i) {
    printf("%d\n", at(&v, i));
  }
  // printf("%ld\n", time(NULL) - start);
  return 0;
}
