#ifndef vector_h
#define vector_h

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define BASE_CAPACITY 1

typedef int Type;

struct vector {
  Type* data_new;
  Type* data_old;
  size_t size;
  size_t capacity;
  size_t mv_iter;
};

bool empty(struct vector*);
size_t capacity(struct vector*);
// size_t find(struct vector*, Type);
size_t size(struct vector*);
Type at(struct vector*, size_t);
// Type back(struct vector*);
// Type front(struct vector*);
// Type pop_back(struct vector*);
void clear(struct vector*);
// void erase(struct vector*, size_t, size_t);
void init(struct vector*);
void push_back(struct vector*, Type);
void upgrade(struct vector*);

#endif /* vector_h */
