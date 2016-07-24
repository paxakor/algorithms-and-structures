// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <vector>
#include "utils/arena.hpp"

namespace pkr {

template <typename Type>
class SumClass {
public:
  inline Type operator()(const Type& a, const Type& b) {
    return a + b;
  }
};

template <typename Type, class Function = SumClass<Type> >
class SegmentTree {
public:
  SegmentTree(const Type* const array, size_t len) {
    init(array, len);
  }

  template <typename InputIterator> SegmentTree(InputIterator begin,
                                                InputIterator end) {
    const std::vector<Type> elems(begin, end);
    init(elems.data(), elems.size());
  }

  inline Type get(size_t left, size_t right)  {
    return get(left, right, _root);
  }

private:
  struct NodeType {
    size_t begin;
    size_t end;
    NodeType* left = nullptr;
    NodeType* right = nullptr;
    Type value;
  };

  void init(const Type* const array, size_t len);
  Type get(size_t, size_t, NodeType*);
  NodeType* _root;
  Arena<NodeType> _data;
};

template <typename Uint>
Uint get_max_lower_pow2(Uint n);

template <typename Type, class Function>
void SegmentTree<Type, Function>::init(const Type* const array, size_t len) {
  auto lvl = _data.get(len);
  for (size_t i = 0; i < len; ++i) {
    lvl[i].value = array[i];
    lvl[i].begin = i;
    lvl[i].end = i + 1;
  }

  size_t counter = len;
  while (len > 1) {
    const auto prev = lvl;
    const auto prev_len = counter;
    len = get_max_lower_pow2(prev_len);
    lvl = _data.get(len);
    size_t i = 0;
    while (i < len && 2 * i < prev_len) {
      lvl[i].left = &prev[2 * i];
      lvl[i].begin = prev[2 * i].begin;

      if (2 * i + 1 < prev_len) {
        lvl[i].right = &prev[2 * i + 1];
        lvl[i].end = prev[2 * i + 1].end;
        lvl[i].value = Function{}(prev[2 * i].value,
                                  prev[2 * i + 1].value);
      } else {
        lvl[i].end = prev[2 * i].end;
        lvl[i].value = prev[2 * i].value;
      }
      ++i;
    }
    counter = i;
  }
  _root = &lvl[0];
}

template <typename Type, class Function>
Type SegmentTree<Type, Function>::get(size_t left, size_t right,
                                      NodeType* node) {
  if (!node || node->end <= left || right <= node->begin) {
    return Type{};
  }
  if (left <= node->begin && node->end <= right) {
    return node->value;
  }
  return Function{}(get(left, right, node->left),
                    get(left, right, node->right));
}

template <typename UInt>
UInt get_max_lower_pow2(UInt n) {
  UInt res = 0;
  if (n > 1) {
    res = 1;
    --n;
    while ((n >>= 1) > 0) {
      res <<= 1;
    }
  }
  return res;
}

}  // namespace pkr
