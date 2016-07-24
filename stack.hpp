// Copyright 2016, Pavel Korozevtsev.

#pragma once

#define BASE_CAPACITY 2

template <typename Type>
class Stack {
public:
  Stack();
  ~Stack();
  Type pop();
  void push(const Type&);
  bool empty() const;
  void clear();
private:
  void resize(uint64_t);
  Type* data;
  uint64_t size;
  uint64_t capacity;
};

template <typename Type>
Stack<Type>::Stack() {
  this->capacity = BASE_CAPACITY;
  this->data = new Type[this->capacity];
  this->size = 0;
}

template <typename Type>
Stack<Type>::~Stack() {
  delete[] this->data;
}

template <typename Type>
Type Stack<Type>::pop() {
  --this->size;
  return this->data[this->size];
}

template <typename Type>
void Stack<Type>::push(const Type& val) {
  if (this->size + 1 < this->capacity) {
    this->data[this->size] = val;
    ++this->size;
  } else {
    this->resize(this->capacity * 2);
    this->push(val);
  }
}

template <typename Type>
bool Stack<Type>::empty() const {
  return this->size == 0;
}

template <typename Type>
void Stack<Type>::clear() {
  this->size = 0;
  delete[] this->data;
  this->capacity = BASE_CAPACITY;
  this->data = new Type[this->capacity];
}

template <typename Type>
void Stack<Type>::resize(uint64_t new_capacity) {
  auto new_data = new Type[new_capacity];
  for (uint64_t i = 0; i < this->size && i < new_capacity; ++i) {
    new_data[i] = this->data[i];
  }
  delete[] this->data;
  this->data = new_data;
  this->capacity = new_capacity;
}
