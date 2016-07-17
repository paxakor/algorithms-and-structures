// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <cstddef>
#include <vector>
#include "list_node.hpp"

namespace pkr {

template <typename Type>
class List {
public:

  using Iterator = ListNode<Type>*;

  List();
  ~List();
  Iterator front() const;
  Iterator back() const;
  Iterator find(const Type&) const;
  void clear();
  void push_front(const Type&);
  void push_back(const Type&);
  void insert_before(Iterator, const Type&);
  void insert_after(Iterator, const Type&);
  void remove(Iterator);
  void remove(const Type&);
  size_t size() const;
  std::vector<Type> to_vector() const;
private:
  Iterator _front;
  Iterator _back;
  size_t _size;
};

template <typename Type>
List<Type>::List()
  : _front(nullptr)
  , _back(nullptr)
  , _size(0) {}

template <typename Type>
List<Type>::~List() {
  clear();
}

template <typename Type>
void List<Type>::clear() {
  if (_front != nullptr) {
    delete _front;
  }
  _front = nullptr;
  _back = nullptr;
  _size = 0;
}

template <typename Type>
typename List<Type>::Iterator List<Type>::front() const {
  return _front;
}

template <typename Type>
typename List<Type>::Iterator List<Type>::back() const {
  return _back;
}

template <typename Type>
typename List<Type>::Iterator List<Type>::find(const Type& val) const {
  auto ptr = front();
  while (ptr != nullptr && ptr->value() != val) {
    ptr = ptr->next();
  }
  return ptr;
}

template <typename Type>
void List<Type>::push_front(const Type& val) {
  if (_front != nullptr) {
    insert_before(_front, val);
    _front = _front->prev();
  } else {
    push_back(val);
  }
}

template <typename Type>
void List<Type>::push_back(const Type& val) {
  if (_back != nullptr) {
    insert_after(_back, val);
    _back = _back->next();
  } else {
    if (_back != nullptr) {
      insert_after(_back, val);
      _back = _back->next();
    } else {
      _front = new ListNode<Type>(val);
      _back = _front;
      ++_size;
    }
  }
}

template <typename Type>
void List<Type>::insert_before(typename List<Type>::Iterator ptr, const Type& val) {
  auto new_nd = new ListNode<Type>(val);
  new_nd->set_prev(ptr->prev());
  new_nd->set_next(ptr);
  ptr->set_prev(new_nd);
  if (new_nd->prev() != nullptr) {
    new_nd->prev()->set_next(new_nd);
  }
  ++_size;
}

template <typename Type>
void List<Type>::insert_after(typename List<Type>::Iterator ptr, const Type& val) {
  auto new_nd = new ListNode<Type>(val);
  new_nd->set_prev(ptr);
  new_nd->set_next(ptr->next());
  ptr->set_next(new_nd);
  if (new_nd->next() != nullptr) {
    new_nd->next()->set_prev(new_nd);
  }
  ++_size;
}

template <typename Type>
void List<Type>::remove(typename List<Type>::Iterator ptr) {
  if (ptr == nullptr) {
    return;
  }
  auto pr = ptr->prev();
  auto nx = ptr->next();
  if (ptr == _front) {
    _front = nx;
  }
  if (ptr == _back) {
    _back = pr;
  }
  if (pr != nullptr) {
    pr->set_next(nx);
  }
  if (nx != nullptr) {
    nx->set_prev(pr);
  }
  ptr->set_next(nullptr);
  ptr->set_prev(nullptr);
  delete ptr;
  --_size;
}

template <typename Type>
void List<Type>::remove(const Type& val) {
  remove(find(val));
}

template <typename Type>
size_t List<Type>::size() const {
  return _size;
}

template <typename Type>
std::vector<Type> List<Type>::to_vector() const {
  std::vector<Type> res;
  for (auto ptr = front(); ptr != nullptr; ptr = ptr->next()) {
    res.push_back(ptr->value());
  }
  return res;
}

}
