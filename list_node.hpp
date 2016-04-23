#pragma once

namespace pkr {

template <typename Type>
class ListNode {
public:
  ListNode();
  ListNode(const Type&);
  ~ListNode();
  const ListNode& operator=(const ListNode<Type>&);
  const Type& value() const;
  ListNode<Type>* prev() const;
  ListNode<Type>* next() const;
  void set_prev(ListNode<Type>*);
  void set_next(ListNode<Type>*);
  void clear_prev();
  void clear_next();
  void clear();
private:
  Type _value;
  ListNode<Type>* _prev;
  ListNode<Type>* _next;
};

template <typename Type>
ListNode<Type>::ListNode()
  : _value()
  , _prev(nullptr)
  , _next(nullptr) {}

template <typename Type>
ListNode<Type>::ListNode(const Type& val)
  : _value(val)
  , _prev(nullptr)
  , _next(nullptr) {}

template <typename Type>
ListNode<Type>::~ListNode() {
  clear();
}

template <typename Type>
const Type& ListNode<Type>::value() const {
  return _value;
}

template <typename Type>
ListNode<Type>* ListNode<Type>::prev() const {
  return _prev;
}

template <typename Type>
ListNode<Type>* ListNode<Type>::next() const {
  return _next;
}

template <typename Type>
void ListNode<Type>::set_prev(ListNode<Type>* ptr) {
  _prev = ptr;
}

template <typename Type>
void ListNode<Type>::set_next(ListNode<Type>* ptr) {
  _next = ptr;
}

template <typename Type>
void ListNode<Type>::clear_prev() {
  if (_prev != nullptr) {
    _prev->_next = nullptr;
    delete _prev;
  }
}

template <typename Type>
void ListNode<Type>::clear_next() {
  if (_next != nullptr) {
    _next->_prev = nullptr;
    delete _next;
  }
}

template <typename Type>
void ListNode<Type>::clear() {
  clear_prev();
  clear_next();
}

}
