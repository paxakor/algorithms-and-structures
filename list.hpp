#pragma once

#include <cstddef>
#include "list_node.hpp"

namespace pkr {

template <typename Type>
class List {
public:
  List();
  ~List();
  ListNode<Type>* begin() const;
  ListNode<Type>* end() const;
  ListNode<Type>* find(const Type&) const;
  void clear();
  void push_front(const Type&);
  void push_back(const Type&);
  void insert_before(ListNode<Type>*, const Type&);
  void insert_after(ListNode<Type>*, const Type&);
  void remove(ListNode<Type>*);
  void remove(const Type&);
  size_t size() const;
private:
  ListNode<Type>* _begin;
  ListNode<Type>* _end;
  size_t _size;
};

template <typename Type>
List<Type>::List()
  : _begin(nullptr)
  , _end(nullptr)
  , _size(0) {}

// template <typename Type>
// List<Type>::List(const List<Type>& another_list) {
//   this->_begin = new ListNode<Type>;
//   this->_end = this->_begin;
//   ListNode<Type>* ptr = another_list.begin();
//   while(ptr != another_list.end()) {
//     _end->set(ptr->value());
//     _end->set_next(new ListNode<Type>);
//     ++_end;
//     ++ptr;
//   }
//   this->_end->set_next(nullptr);
// }

// template <typename Type>
// List<Type>::List(const Type* array, size_t length) {
//   this->_begin = new ListNode<Type>;
//   this->_end = _begin;
//   for(size_t i = 0; i < length; ++i) {
//     this->_end->set(array[i]);
//     this->_end->set_next(new ListNode<Type>);
//     this->_end = _end->next();
//   }
//   this->_end->set_next(nullptr);
//   print_list(*this);
// }

template <typename Type>
List<Type>::~List() {
  clear();
}

template <typename Type>
void List<Type>::clear() {
  if (_begin != nullptr) {
    delete _begin;
  }
  _begin = nullptr;
  _end = nullptr;
  _size = 0;
}

template <typename Type>
ListNode<Type>* List<Type>::begin() const {
  return _begin;
}

template <typename Type>
ListNode<Type>* List<Type>::end() const {
  return _end;
}

template <typename Type>
ListNode<Type>* List<Type>::find(const Type& val) const {
  ListNode<Type>* ptr = begin();
  while (ptr != nullptr && ptr->value() != val) {
    ptr = ptr->next();
  }
  return ptr;
}

template <typename Type>
void List<Type>::push_front(const Type& val) {
  if (_begin != nullptr) {
    insert_before(_begin, val);
  } else {
    push_back(val);
  }
}

template <typename Type>
void List<Type>::push_back(const Type& val) {
  if (_end != nullptr) {
    insert_after(_end, val);
    _end = _end->next();
  } else {
    if (_begin != nullptr) {
      insert_after(_begin, val);
      _end = _begin->next();
    } else {
      _begin = new ListNode<Type>(val);
      ++_size;
    }
  }
}

template <typename Type>
void List<Type>::insert_before(ListNode<Type>* ptr, const Type& val) {
  ListNode<Type>* new_nd = new ListNode<Type>(val);
  new_nd->set_prev(ptr->prev());
  new_nd->set_next(ptr);
  ptr->set_prev(new_nd);
  if (new_nd->prev() != nullptr) {
    new_nd->prev()->set_next(new_nd);
  }
  ++_size;
}

template <typename Type>
void List<Type>::insert_after(ListNode<Type>* ptr, const Type& val) {
  ListNode<Type>* new_nd = new ListNode<Type>(val);
  new_nd->set_prev(ptr);
  new_nd->set_next(ptr->next());
  ptr->set_next(new_nd);
  if (new_nd->next() != nullptr) {
    new_nd->next()->set_prev(new_nd);
  }
  ++_size;
}

template <typename Type>
void List<Type>::remove(ListNode<Type>* ptr) {
  if (ptr == nullptr) {
    return;
  }
  auto pr = ptr->prev();
  auto nx = ptr->next();
  if (ptr == _begin) {
    _begin = nx;
  }
  if (ptr == _end) {
    _end = pr;
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

}
