#include <stdio.h>
#include "vector.h"

#define RADIX 2

void init(struct vector* vec) {
  vec->data_new    = malloc(BASE_CAPACITY * sizeof(Type) * RADIX);
  vec->data_old    = malloc(BASE_CAPACITY * sizeof(Type));
  vec->size        = 0;
  vec->capacity    = BASE_CAPACITY;
  vec->mv_iter     = 0;
}

bool empty(struct vector* vec) {
  return (vec->size == 0);
}

size_t capacity(struct vector* vec) {
  return vec->capacity;
}

size_t size(struct vector* vec) {
  return vec->size;
}

Type at(struct vector* vec, size_t iter) {
  if (iter < vec->size) {
    return vec->data_old[iter];
  } else {
    fprintf(stderr, "error: in function vector.at: iter >= vector.size\n");
    return 0;
  }
}

void clear(struct vector* vec) {
  free(vec->data_old);
  free(vec->data_new);
  init(vec);
}

void push_back(struct vector* vec, Type val) {
  if (vec->size + 1 < vec->capacity) {
    vec->data_old[vec->size] = val;
    ++vec->size;
    if (vec->mv_iter < vec->size) {
      for (int i = 0; i < RADIX + 1; ++i) {
        vec->data_new[vec->mv_iter] = vec->data_old[vec->mv_iter];
        ++vec->mv_iter;
      }
    }
  } else {
    upgrade(vec);
    push_back(vec, val);
  }
}

void upgrade(struct vector* vec) {
  free(vec->data_old);
  vec->data_old = vec->data_new;
  vec->capacity = vec->capacity * RADIX;
  vec->data_new = malloc(vec->capacity * sizeof(Type) * RADIX);
  // vec->data_new = calloc(vec->capacity * 2, sizeof(Type));
  vec->mv_iter = 0;
}
