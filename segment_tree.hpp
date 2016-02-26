#pragma once

#include <cinttypes>
#include "tree.hpp"

template <typename Type>
class SegmentTree {
public:
  SegmentTree(const Type* const, uint64_t);
  ~SegmentTree();
  Type get(uint64_t, uint64_t);
private:
  struct NodeType {
    Type value;
    uint64_t left;
    uint64_t right;
  };

  Type get(uint64_t, uint64_t, TreeNode<NodeType>*);
  TreeNode<NodeType>* root;
  uint64_t size;
};

template <typename UINT>
UINT get_max_lower_pow2(UINT n);

template <typename Type>
SegmentTree<Type>::SegmentTree(const Type* const array, uint64_t len) {
  this->size = len;
  TreeNode<NodeType>* prev;
  TreeNode<NodeType>* lvl;
  lvl = new TreeNode<NodeType>[len];
  for (uint64_t i = 0; i < len; ++i) {
    lvl[i].value.value = array[i];
    lvl[i].value.left = i;
    lvl[i].value.right = i + 1;
    lvl[i].parent = nullptr;
    lvl[i].child_left = nullptr;
    lvl[i].child_right = nullptr;
  }
  uint64_t counter = len;
  while (len > 1) {
    prev = lvl;
    auto prev_len = counter;
    len = get_max_lower_pow2(prev_len);
    lvl = new TreeNode<NodeType>[len];
    uint64_t i = 0;
    while (i < len && 2 * i < prev_len) {
      lvl[i].parent = nullptr;
      lvl[i].child_left = &prev[2 * i];
      lvl[i].value.left = prev[2 * i].value.left;
      prev[2 * i].parent = &lvl[i];

      if (2 * i + 1 < prev_len) {
        lvl[i].child_right = &prev[2 * i + 1];
        lvl[i].value.value = prev[2 * i].value.value + prev[2 * i + 1].value.value;
        lvl[i].value.right = prev[2 * i + 1].value.right;
        prev[2 * i + 1].parent = &lvl[i];
      } else {
        lvl[i].child_right = nullptr;
        lvl[i].value.value = prev[2 * i].value.value;
        lvl[i].value.right = prev[2 * i].value.right;
      }
      ++i;
    }
    counter = i;
  }
  this->root = &lvl[0];
}

template <typename Type>
SegmentTree<Type>::~SegmentTree() {
  delete root;
}

template <typename Type>
Type SegmentTree<Type>::get(uint64_t left, uint64_t right) {
  return this->get(left, right, this->root);
}

template <typename Type>
Type SegmentTree<Type>::get(uint64_t left, uint64_t right, TreeNode<NodeType>* node) {
  Type res;
  if (node->value.right <= left || right <= node->value.left) {
    res = Type();
  } else if (left <= node->value.left && node->value.right <= right) {
    res = node->value.value;
  } else {
    res = get(left, right, node->child_left) + \
      get(left, right, node->child_right);
  }
  return res;
}

template <typename UINT>
UINT get_max_lower_pow2(UINT n) {
  UINT res;
  if (n < 2) {
    res = 0;
  } else {
    res = 1;
    --n;
    while ((n = n >> 1) > 0) {
      res = res << 1;
    }
  }
  return res;
}
