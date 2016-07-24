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
  Type* _data;
  uint64_t _size;
  uint64_t _capacity;
};

template <typename Type>
Stack<Type>::Stack()
  : _capacity(BASE_CAPACITY)
  , _data(new Type[_capacity])
  , _size(0){}

template <typename Type>
Stack<Type>::~Stack() {
  delete[] _data;
}

template <typename Type>
Type Stack<Type>::pop() {
  --_size;
  return _data[_size];
}

template <typename Type>
void Stack<Type>::push(const Type& val) {
  if (_size + 1 < _capacity) {
    _data[_size] = val;
    ++_size;
  } else {
    _resize(_capacity * 2);
    _push(val);
  }
}

template <typename Type>
bool Stack<Type>::empty() const {
  return _size == 0;
}

template <typename Type>
void Stack<Type>::clear() {
  _size = 0;
  delete[] _data;
  _capacity = BASE_CAPACITY;
  _data = new Type[_capacity];
}

template <typename Type>
void Stack<Type>::resize(uint64_t new_capacity) {
  auto new_data = new Type[new_capacity];
  for (uint64_t i = 0; i < _size && i < new_capacity; ++i) {
    new_data[i] = _data[i];
  }
  delete[] _data;
  _data = new_data;
  _capacity = new_capacity;
}
