#pragma once

#include <cstddef>

template <typename Type>
class Heap {
public:
  Heap();
  Heap(const Type* const, const size_t, const size_t);
  ~Heap();
  Type get_max() const;
  void add(const Type&);
  void del_max();
private:
  void sift_up(size_t);
  void sift_down(size_t);
  void realloc();
  inline size_t parent(size_t) const;
  inline size_t child(size_t, size_t) const;

  size_t size;
  size_t k;
  size_t capacity;
  Type* data;
};

template <typename Type>
Heap<Type>::Heap() {
  this->k = 2;
  this->capacity = 16;
  this->size = 0;
  this->data = new Type[this->capacity];
}

template <typename Type>
Heap<Type>::Heap(const Type* const array, const size_t len, const size_t k) {
  this->k = k;
  this->size = len;
  this->capacity = len;
  this->data = new Type[this->capacity];
  for (size_t i = 0; i < len; ++i) {
    data[i] = array[i];
  }
  for (size_t i = len; 0 < i; --i) {
    this->sift_up(i - 1);
  }
}

template <typename Type>
Heap<Type>::~Heap() {
  delete[] this->data;
}

template <typename Type>
Type Heap<Type>::get_max() const {
  return this->data[0];
}

template <typename Type>
void Heap<Type>::add(const Type& val) {
  if (this->size + 1 >= this->capacity) {
    this->realloc();
  }
  this->data[this->size] = val;
  this->sift_up(this->size);
  ++this->size;
}

template <typename Type>
void Heap<Type>::del_max() {
  if (this->size < 2) {
    return;
  }
  --this->size;
  this->data[0] = this->data[this->size];
  this->sift_down(0);
}

template <typename Type>
void Heap<Type>::sift_up(size_t iter) {
  auto& a = this->data[iter];
  auto& b = this->data[parent(iter)];
  if (a > b) {
    auto tmp = a;
    a = b;
    b = tmp;
    this->sift_up(parent(iter));
  }
}

template <typename Type>
void Heap<Type>::sift_down(size_t iter) {
  if (iter >= this->size) {
    return;
  }
  auto i = 0;
  auto max = iter;
  while (true) {
    auto child = this->child(iter, i);
    if (child == 0) {
      break;
    }
    if (this->data[child] > this->data[max]) {
      max = child;
    }
    ++i;
  }
  if (max == iter) {
    return;
  }
  auto tmp = this->data[max];
  this->data[max] = this->data[iter];
  this->data[iter] = tmp;
  this->sift_down(max);
}

template <typename Type>
void Heap<Type>::realloc() {
  size_t new_capacity = 2 * this->capacity;
  Type* new_data = new Type[new_capacity];
  for (size_t i = 0; i < this->capacity; ++i) {
    new_data[i] = this->data[i];
  }
  delete[] this->data;
  this->data = new_data;
  this->capacity = new_capacity;
}

template <typename Type>
size_t Heap<Type>::parent(size_t iter) const {
  if (iter == 0) {
    return 0;
  }
  return ((iter + 1) / this->k) - 1;
}

// number in [0, k-1].
template <typename Type>
size_t Heap<Type>::child(size_t iter, size_t number) const {
  auto ans = ((iter + 1) * this->k + number) - 1;
  if (ans >= this->size) {
    return 0;
  }
  return ans;
}
