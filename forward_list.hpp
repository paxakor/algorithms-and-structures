// Copyright 2017, Pavel Korozevtsev.

#pragma once

#include <cstddef>
#include <memory>

namespace pkr {

template <typename Type> class ForwardList;

namespace detail {

template <typename Type>
struct ForwardListNode {
  using ConstNodePointer = const std::shared_ptr<ForwardListNode<Type>>;
  using NodePointer = std::shared_ptr<ForwardListNode<Type>>;

  ForwardListNode() = default;
  explicit ForwardListNode(const Type& v) : value(v) {};

  Type value;
  NodePointer next;
};

template <typename Type>
struct ForwardListIterator {
public:
  using Node           = ForwardListNode<Type>;
  using NodePointer    = typename Node::NodePointer;
  using ConstReference = const Type&;
  using Reference      = Type&;
  using ConstPointer   = const Type*;
  using Pointer        = Type*;

  ForwardListIterator() = default;
  ForwardListIterator(NodePointer p) : item(p) {}
  ForwardListIterator(std::nullptr_t p)   : item(p) {}
  ForwardListIterator& operator=(const ForwardListIterator&) = default;

  bool                 operator==(const ForwardListIterator&) const;
  bool                 operator!=(const ForwardListIterator&) const;
  ConstPointer         operator->() const;
  Pointer              operator->();
  ConstReference       operator*() const;
  Reference            operator*();
  ForwardListIterator& operator++();
  ForwardListIterator  operator++(int);

private:
  friend class ForwardList<Type>;
  NodePointer item;
};

template <typename Type> bool
ForwardListIterator<Type>::operator==(const ForwardListIterator& rhs) const {
  return item == rhs.item;
}

template <typename Type> bool
ForwardListIterator<Type>::operator!=(const ForwardListIterator& rhs) const {
  return !(*this == rhs);
}

template <typename Type>
typename ForwardListIterator<Type>::ConstPointer
ForwardListIterator<Type>::operator->() const {
  return &item->value;
}

template <typename Type>
typename ForwardListIterator<Type>::Pointer
ForwardListIterator<Type>::operator->() {
  return &item->value;
}

template <typename Type>
typename ForwardListIterator<Type>::ConstReference
ForwardListIterator<Type>::operator*() const {
  return item->value;
}

template <typename Type>
typename ForwardListIterator<Type>::Reference
ForwardListIterator<Type>::operator*() {
  return item->value;
}

template <typename Type>
ForwardListIterator<Type>& ForwardListIterator<Type>::operator++() {
  item = item->next;
  return *this;
}

template <typename Type>
ForwardListIterator<Type> ForwardListIterator<Type>::operator++(int) {
  const auto tmp = *this;
  ++*this;
  return tmp;
}

}  // namespace detail


template <typename Type>
class ForwardList {
public:
  using Node           = detail::ForwardListNode<Type>;
  using NodePointer    = typename Node::NodePointer;
  using Iterator       = detail::ForwardListIterator<Type>;
  using ConstIterator  = const Iterator;
  using ConstReference = const Type&;
  using Reference      = Type&;

  ConstReference front() const;
  Reference      front();
  ConstIterator  begin() const;
  Iterator       begin();
  ConstIterator  end() const;
  Iterator       end();
  void clear();
  void erase_after(Iterator);
  void insert_after(Iterator, ConstReference);
  void push_front(ConstReference);
  void pop_front();

private:
  NodePointer first;
};

template <typename Type>
typename ForwardList<Type>::ConstReference
ForwardList<Type>::front() const {
  return first->value;
}

template <typename Type>
typename ForwardList<Type>::Reference
ForwardList<Type>::front() {
  return first->value;
}

template <typename Type>
typename ForwardList<Type>::Iterator
ForwardList<Type>::begin() {
  return first;
}

template <typename Type>
typename ForwardList<Type>::Iterator
ForwardList<Type>::end() {
  return nullptr;
}

template <typename Type>
typename ForwardList<Type>::ConstIterator
ForwardList<Type>::begin() const {
  return first;
}

template <typename Type>
typename ForwardList<Type>::ConstIterator
ForwardList<Type>::end() const {
  return nullptr;
}

template <typename Type>
void ForwardList<Type>::clear() {
  first = nullptr;
}

template <typename Type>
void ForwardList<Type>::erase_after(Iterator iter) {
  NodePointer pos = iter.item;
  if (pos && pos->next) {
    pos->next = pos->next->next;
  }
}

template <typename Type>
void ForwardList<Type>::insert_after(Iterator pos, ConstReference val) {
  auto new_nd = std::make_shared<Node>(val);
  new_nd->next = pos->next;
  pos->next = new_nd;
}

template <typename Type>
void ForwardList<Type>::push_front(ConstReference val) {
  auto new_nd = std::make_shared<Node>(val);
  new_nd->next = first;
  first = new_nd;
}

template <typename Type>
void ForwardList<Type>::pop_front() {
  first = first->next;
}

}  // namespace pkr
